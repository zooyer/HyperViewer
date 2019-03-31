package server

import (
	"net"
	"sync"
	"errors"
	"io"
	"log"
	"context"
)

const brokerMaxConnection = 1024

type Broker interface {
	Simplex(in net.Conn, out net.Conn) error
	Duplex(one net.Conn, two net.Conn) error
}

func NewBroker() Broker {
	return newBroker()
}

type broker struct {
	mutex   sync.Mutex
	count   int
}

func newBroker() *broker {
	return new(broker)
}

// Simplex Communication : in -> out
func (b *broker) Simplex(in net.Conn, out net.Conn) error {
	b.mutex.Lock()
	if b.count + 1 > brokerMaxConnection {
		return errors.New("exceeded the maximum number of connections")
	}
	b.count++
	b.mutex.Unlock()

	defer in.Close()
	defer out.Close()

	var err error
	var buf = make([]byte, 4096 * 4)
	for true {
		if _,err = ReaderToWriter(out, in, buf); err != nil {
			log.Println("Simplex Error:", err.Error())
			break
		}
	}

	return err
}

// Full Duplex : ont <--> two
func (b *broker) Duplex(one net.Conn, two net.Conn) error {
	b.mutex.Lock()
	if b.count + 1 > brokerMaxConnection {
		return errors.New("exceeded the maximum number of connections")
	}
	b.count++
	b.mutex.Unlock()

	defer one.Close()
	defer two.Close()

	var err error
	var ctx,cancel = context.WithCancel(context.Background())
	var ott = make([]byte, 4096 * 4)
	var tto = make([]byte, 4096 * 4)

	go func() {
		ctx,_ := context.WithCancel(ctx)
		for {
			select {
			case <-ctx.Done():
				{
					log.Println("ott done!")
					return
				}
			default:
				{
					if _,err = CopyBuffer(two, one, ott); err != nil {
						cancel()
						log.Println("FullDuplex Error <ott>:", err.Error())
					}
				}
			}
		}
	}()

	func() {
		for {
			select {
			case <-ctx.Done():
				{
					log.Println("tto done!")
					return
				}
			default:
				{
					if _,err = CopyBuffer(one, two, tto); err != nil {
						cancel()
						log.Println("FullDuplex Error <tto>:", err.Error())
					}
				}
			}
		}
	}()

	return err
}

//
func ReaderToWriter(writer io.Writer, reader io.Reader, buf []byte) (written int64, err error) {
	if buf == nil {
		return 0, errors.New("empty buffer")
	}
	nr, err := reader.Read(buf)
	if nr > 0 {
		nw, ew := writer.Write(buf[0:nr])
		if nw > 0 {
			written += int64(nw)
		}
		if ew != nil {
			return written, ew
		}
		if nr != nw {
			return written, io.ErrShortWrite
		}
	}

	return
}

// CopyBuffer like io.CopyBuffer, but don't ignore EOF.
func CopyBuffer(writer io.Writer, reader io.Reader, buf []byte) (written int64, err error) {
	for {
		n,err := ReaderToWriter(writer, reader, buf)
		if n > 0 {
			written += n
		}
		if err != nil {
			return written, err
		}
	}
	return written, err
}
