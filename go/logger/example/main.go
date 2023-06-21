package main

import "github.com/black-desk/lib/go/logger"

func main() {
	log := logger.Get("example")
	log.Debug("1---")
	log.Info("2---")
	log.Warn("3---")
	log.Error("4---")
}
