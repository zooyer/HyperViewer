package server

import (
	"net"
	"time"
	"sync"
)

const defaultRegisterTimeout time.Duration = time.Hour

//go get github.com/UncleBig/goCache

type HoleServer interface {
	SetAddress(key string, ipAddr net.Addr, timeout time.Duration)
	GetAddress(key string) net.Addr
	RemoveAddress(key string)
}

func NewHoleServer() HoleServer {
	return newHole()
}

type addr struct {
	addr    net.Addr
	time    time.Time
	timeout time.Duration
}

type hole struct {
	mutex  sync.RWMutex
	store  map[string] addr
}

func newHole() *hole {
	var h = new(hole)
	h.store = make(map[string] addr)

	return h
}

func (h *hole) SetAddress(key string, ipAddr net.Addr, timeout time.Duration) {
	h.mutex.Lock()
	defer h.mutex.Unlock()

	h.store[key] = addr{addr:ipAddr, time:time.Now(), timeout:timeout}
}

func (h *hole) GetAddress(key string) net.Addr {
	h.mutex.RLock()
	defer h.mutex.RUnlock()

	if addr,ok := h.store[key]; ok {
		if addr.time.Add(addr.timeout).After(time.Now()) {
			return addr.addr
		}
	}

	return nil
}

func (h *hole) RemoveAddress(key string) {
	h.mutex.Lock()
	defer h.mutex.Unlock()

	delete(h.store, key)
}
