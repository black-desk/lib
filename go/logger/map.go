package logger

import (
	"sync"

	"go.uber.org/zap"
)

var loggerMap = sync.Map{}

func Get(name string) *zap.SugaredLogger {
	value, _ := loggerMap.LoadOrStore(name, newLogger(name))

	log, ok := value.(*zap.SugaredLogger)
	if !ok {
		panic("logger type error")
	}

	return log
}
