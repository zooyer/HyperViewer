package server

import (
	"testing"
	"net"
	"fmt"
	"encoding/json"
	"os"
	"runtime"
	"golang.org/x/sys/windows"
	"unsafe"
)

type SystemInformation struct {
	GUID           string         `json:"guid"`
	UUID           string         `json:"uuid"`
	OS             string         `json:"os"`
	Arch           string         `json:"arch"`
	System         string         `json:"system"`
	Version        string         `json:"version"`
	Hostname       string         `json:"hostname"`
	CPU            []string       `json:"cpu"`
	Disk           []HardDisk     `json:"disk"`
	Memory         []Memory       `json:"memory"`
	Network        []NetworkCard  `json:"network"`
}

type CPU   struct {
	Name     string      `json:"name"`
	Model    string      `json:"model"`      // device model
	UUID     string      `json:"uuid"`

	//Used     uint64      `json:"used"`
	//Free     uint64      `json:"free"`
}

type Memory struct {
	Name     string      `json:"name"`
	Model    string      `json:"model"`      // device model
	UUID     string      `json:"uuid"`

	//Used     uint64      `json:"used"`
	//Free     uint64      `json:"free"`
	//Capacity uint64      `json:"capacity"`
}

type Partition struct {
	Name     string      `json:"name"`    // partition name
	Volume   string      `json:"volume"` // volume name

	FS       string      `json:"fs"`      // file system
	Used     uint64      `json:"used"`
	Free     uint64      `json:"free"`
	Capacity uint64      `json:"capacity"`
}

type HardDisk struct {
	Name     string       `json:"name"`       // device name
	Model    string       `json:"model"`      // device model
	UUID     string      `json:"uuid"`

	//Partition []Partition `json:"partition"` // disk partition
}

type Address struct {
	IP       []byte      `json:"ip"`        // ipv4: 4 byte, ipv6: 16 byte
	Mask     []byte      `json:"mask"`     // subnet mask
	Subnet   int         `json:"subnet"`   // subnet prefix length
	Gateway  []byte      `json:"gateway"`  // default gateway
}

type NetworkCard struct {
	Name     string      `json:"name"`     // device name
	MTU      int         `json:"mtu"`      // max transmission unit
	MAC      []byte      `json:"mac"`      // physical address
	UUID     string      `json:"uuid"`
	//Addr     []Address   `json:"addr"`     // ip address
}

func GetMachineGuid() (string, error) {
	// register: HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Cryptography\MachineGuid
	// there has been reports of issues on 32bit using golang.org/x/sys/windows/registry, see https://github.com/shirou/gopsutil/pull/312#issuecomment-277422612
	// for rationale of using windows.RegOpenKeyEx/RegQueryValueEx instead of registry.OpenKey/GetStringValue
	var h windows.Handle
	err := windows.RegOpenKeyEx(windows.HKEY_LOCAL_MACHINE, windows.StringToUTF16Ptr(`SOFTWARE\Microsoft\Cryptography`), 0, windows.KEY_READ|windows.KEY_WOW64_64KEY, &h)
	if err != nil {
		return "", err
	}
	defer windows.RegCloseKey(h)

	const windowsRegBufLen = 74 // len(`{`) + len(`abcdefgh-1234-456789012-123345456671` * 2) + len(`}`) // 2 == bytes/UTF16
	const uuidLen = 36

	var regBuf [windowsRegBufLen]uint16
	bufLen := uint32(windowsRegBufLen)
	var valType uint32
	err = windows.RegQueryValueEx(h, windows.StringToUTF16Ptr(`MachineGuid`), nil, &valType, (*byte)(unsafe.Pointer(&regBuf[0])), &bufLen)
	if err != nil {
		return "", err
	}

	hostID := windows.UTF16ToString(regBuf[:])
	hostIDLen := len(hostID)
	if hostIDLen != uuidLen {
		return "", fmt.Errorf("HostID incorrect: %q\n", hostID)
	}

	return hostID, nil
}

func TestSystemInformation(t *testing.T) {
	fmt.Println(runtime.GOROOT())
	id,err := GetMachineGuid()
	if err != nil {
		panic(err)
	}
	fmt.Println("id:", id)
	fmt.Println(runtime.NumCPU())
	fmt.Println(os.Hostname())
	nc := NetworkCard{
		Name:"name",
		MTU:1400,
		MAC:[]byte{0xff, 0x2b, 0xa4, 0x73, 0xaa, 0x1b},
	}
	js,err := json.Marshal(nc)
	if err != nil {
		panic(err)
	}
	fmt.Println(string(js))
	var nc2 NetworkCard
	if err = json.Unmarshal(js, &nc2); err != nil {
		panic(err)
	}
	fmt.Println(nc2)

	nets,err := net.Interfaces()
	if err != nil {
		panic(err)
	}
	if nets == nil {
		panic("nets is <nil>")
	}

	for i,_ := range nets {
		fmt.Println(nets[i].Name)
		nets[i].MulticastAddrs()
		addr,err := nets[i].Addrs()
		if err != nil { panic(err) }
		for j,_ := range addr {
			if ip,ok := addr[j].(*net.IPNet); ok {
				fmt.Println("ip:", ip.String())
			} else {
				fmt.Println("no ip")
			}
		}
		fmt.Println()
	}
}