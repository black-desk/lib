package logger

import (
	"sync"

	"go.uber.org/zap"
)

var loggerMap = sync.Map{}

func Get(name string) *zap.SugaredLogger {
	value, _ := loggerMap.LoadOrStore(name, newLogger(name))
	log, _ := value.(*zap.SugaredLogger)
	return log
}
