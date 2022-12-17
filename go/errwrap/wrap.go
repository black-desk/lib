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
	return fmt.Errorf("%s:%d\n%w", file, line, err)
}

func Annotate(err error, message string, a ...any) error {
	_, file, line, ok := runtime.Caller(1)
	if !ok {
		panic("failed to get caller")
	}

	return fmt.Errorf(
		"%s:%d [%v]\n%w", file, line, fmt.Sprintf(message, a...), err,
	)
}
