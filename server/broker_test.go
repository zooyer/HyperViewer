package server

import (
	"testing"
	"fmt"
	"time"
	"context"
	"sync"
	"net"
	"net/http"
	"log"
	_ "net/http/pprof"
	)

func doWithCancel(ctx context.Context) {
	for {
		select {
		case <-ctx.Done():
			fmt.Println("done")
			return
		default:
			fmt.Println("WithCancel...")
			time.Sleep(time.Second)
		}
	}
}

func withCancel() {
	ctx,cancel := context.WithCancel(context.Background())
	go doWithCancel(ctx)
	time.Sleep(3 * time.Second)
	cancel()
	time.Sleep(time.Second)
}

func withTimeout() {
	ctx,cancel := context.WithTimeout(context.Background(), time.Second * 5)
	go doWithCancel(ctx)
	//time.Sleep(3 * time.Second)
	time.Sleep(7 * time.Second)
	cancel()
}

func withDeadline() {
	ctx,cancel := context.WithDeadline(context.Background(), time.Now().Add(2 * time.Second))
	go doWithCancel(ctx)
	cancel()
	time.Sleep(3 * time.Second)
}

func withAllContext() {
	ctx,cancel := context.WithTimeout(context.Background(), 5 * time.Second)

	c1,_ := context.WithTimeout(ctx, 6 * time.Second)
	c2,_ := context.WithTimeout(ctx, 8 * time.Second)
	c3,_ := context.WithTimeout(ctx, 1 * time.Second)
	c4,_ := context.WithTimeout(c3, 2 * time.Second)

	var wg sync.WaitGroup
	wg.Add(4)

	go func() {
		defer wg.Done()
		for {
			select {
			case <-c1.Done():
				fmt.Println("c1 done.")
				return
			}
		}
	}()
	go func() {
		defer wg.Done()
		for {
			select {
			case <-c2.Done():
				fmt.Println("c2 done.")
				return
			}
		}
	}()
	go func() {
		defer wg.Done()
		for {
			select {
			case <-c3.Done():
				fmt.Println("c3 done.")
				return
			}
		}
	}()
	go func() {
		defer wg.Done()
		for {
			select {
			case <-c4.Done():
				fmt.Println("c4 done.")
				return
			}
		}
	}()

	time.Sleep(time.Second)
	cancel()

	wg.Wait()
}

func TestContext(t *testing.T) {
	ctx,cancel := context.WithCancel(context.Background())
	c1,_ := context.WithCancel(ctx)

	go func() {
		time.Sleep(3 * time.Second)
		cancel()
		cancel()
	}()

	go func() {
		for {
			select {
			case <-c1.Done(): {
				fmt.Println("c1 done...")
				return
			}
			}
		}
	}()

	func() {
		for {
			select {
			case <-ctx.Done(): {
				fmt.Println("ctx done...")
				return
			}
			}
		}
	}()

	return

	withAllContext()
	return
	withDeadline()
	withTimeout()
	withCancel()
}

func TestNewBroker(t *testing.T) {
	var b = NewBroker()

	listener,err := net.Listen("tcp", ":9999")
	if err != nil {
		panic(err)
	}

	go func() {
		log.Fatal(http.ListenAndServe("0.0.0.0:8080", nil))
	}()

	for {
		conn1,err := listener.Accept()
		if err != nil {
			panic(err)
		}
		conn2,err := listener.Accept()
		if err != nil {
			panic(err)
		}

		fmt.Println(fmt.Sprintf("connection:<%s> -> <%s>", conn1.RemoteAddr(), conn2.RemoteAddr()))

		go func() {
			//if err = b.Simplex(conn1, conn2); err != nil {
			//	panic(err)
			//}
			if err = b.Duplex(conn1, conn2); err != nil {
				panic(err)
			}
		}()
	}
}