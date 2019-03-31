package server

type User struct {
	ID         int
	UID        int
	UserId     string
	Username   string
	Password   string

	Role       string
	Status     string

	NickName   string
	RealName   string
	Signature  string
	Sex        bool
	Avatar     string
	Email      string
	Phone      int
	Address    string

	CreateTime int64
	UpdateTime int64

	RegisterTime int64
	RegisterIp   string

	LoginTime    int64
	LoginIp      string

	AccessToken  string
	AccessExpire int64
}

type Authorization struct {
	ID    int
	UserId int
	IdentityType int
	Identifier   string
	Credential   string
}