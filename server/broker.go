package server

import (
	"net"
	"sync"
	"github.com/qiniu/errors"
	"io"
	"log"
)

const brokerMaxConnection = 1024

type Broker interface {
	Simplex(in net.Conn, out net.Conn) error
	HalfDuplex(one net.Conn, two net.Conn) error
	FullDuplex(one net.Conn, two net.Conn) error
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
		if _,err = io.CopyBuffer(out, in, buf); err != nil {
			log.Println("Simplex Error:", err.Error())
			break
		}
	}

	return err
}

func (b *broker) HalfDuplex(one net.Conn, two net.Conn) error {
	b.mutex.Lock()
	if b.count + 1 > brokerMaxConnection {
		return errors.New("exceeded the maximum number of connections")
	}
	b.count++
	b.mutex.Unlock()

	defer one.Close()
	defer two.Close()

	var err error
	var buf = make([]byte, 4096 * 4)
	for true {
		if _,err = CopyBuffer(one, two, buf); err != nil {
			log.Println("Simplex Error <one -> two>:", err.Error())
			return err
		}
		if _,err = CopyBuffer(two, one, buf); err != nil {
			log.Println("Simplex Error <two -> one>:", err.Error())
			return err
		}
	}

	return err
}

func (b *broker) FullDuplex(one net.Conn, two net.Conn) error {
	b.mutex.Lock()
	if b.count + 1 > brokerMaxConnection {
		return errors.New("exceeded the maximum number of connections")
	}
	b.count++
	b.mutex.Unlock()

	defer one.Close()
	defer two.Close()

	var err error
	var buf = make([]byte, 4096 * 4)

	for true {
		if _,err = CopyBuffer(one, two, buf); err != nil {
			log.Println("Simplex Error <one -> two>:", err.Error())
			return err
		}
		if _,err = CopyBuffer(two, one, buf); err != nil {
			log.Println("Simplex Error <two -> one>:", err.Error())
			return err
		}
	}

	return err
}


func CopyBuffer(reader io.Reader, writer io.Writer, buff []byte) (n int64, err error) {
	var written int64 = 0
	nr,err := reader.Read(buff)
	if nr > 0 {
		nw,err := writer.Write(buff[0:nr])
		if nw > 0 {
			written += int64(nw)
		}
		if err != nil {
			return 0, err
		}
		if nr != nw {
			return 0, io.ErrShortWrite
		}
	}
	if err != nil {
		return 0, err
	}

	return written, nil
}

func aaa()  {

}