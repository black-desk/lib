package logger

import (
	"sync"

	"go.uber.org/zap"
)

var loggerMapMutex sync.Mutex
var loggerMap = map[string]*zap.SugaredLogger{}

func Get(name string) *zap.SugaredLogger {
	loggerMapMutex.Lock()
	defer loggerMapMutex.Unlock()

	oldLog, ok := loggerMap[name]
	if ok {
		return oldLog
	}

	newLog := newLogger(name)
	loggerMap[name] = newLog

	return newLog
}
