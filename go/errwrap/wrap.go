package errwrap

import (
	"fmt"
	"runtime"
)

func Trace(err error) error {
	_, file, line, ok := runtime.Caller(1)
	if !ok {
		panic("failed to get caller")
	}
	return fmt.Errorf("%s:%d %w", file, line, err)
}

func Annotate(err error, message string) error {
	_, file, line, ok := runtime.Caller(1)
	if !ok {
		panic("failed to get caller")
	}

	return fmt.Errorf("%s:%d [%v] %w", file, line, message, err)
}
