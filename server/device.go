package server

type Device struct {
	ID         int
	UID        int
	DeviceId   string

	CreateTime int64
	UpdateTime int64

	RegisterTime int64
	RegisterIp   string

	LoginTime    int64
	LoginIp      string

	AccessToken  string
	AccessExpire int64
}