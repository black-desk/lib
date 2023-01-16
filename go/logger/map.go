package logger

import (
	"errors"
	"sync"

	"go.uber.org/zap"
)

var loggerMapMutex sync.Mutex
var loggerMap = map[string]any{}

func Get(name string) *zap.SugaredLogger {
	loggerMapMutex.Lock()
	defer loggerMapMutex.Unlock()

	oldLog, ok := loggerMap[name]
	if ok {
		return oldLog.(*zap.SugaredLogger)
	}

	newLog := newLogger(name)
	return newLog
}

func SetLogger(logger *zap.SugaredLogger) func(logger *zap.SugaredLogger) error {
	return func(newLogger *zap.SugaredLogger) error {
		if newLogger == nil {
			return ErrNilLogger
		}
		logger = newLogger
		return nil
	}
}

var ErrNilLogger = errors.New("nil logger")
