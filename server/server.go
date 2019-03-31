package server

type Server struct {
	hole   HoleServer
	broker Broker
}

// OAuth2.0
func (s *Server) Login(username, password string) {

}

// device is online
func Online() bool {
	return false
}

func Logout() {

}

func Connect() {

}