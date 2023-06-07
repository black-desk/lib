package errwrap_test

import (
	"errors"
	"fmt"
	"runtime"
	"strings"
	"testing"

	. "github.com/smartystreets/goconvey/convey"

	. "github.com/black-desk/lib/go/errwrap"
)

type MyError struct{}

func (e *MyError) Error() string {
	return "example error for test"
}

func (e *MyError) Is(target error) bool {
	if _, ok := target.(*MyError); !ok {
		return false
	}
	return true
}

func TestWrap(t *testing.T) {
	Convey("Create a traced error", t, func() {
		var err error
		err = &MyError{}
		Wrap(&err)
		_, _, line, _ := runtime.Caller(0)

		errStr := err.Error()

		Convey("The error should contain file name", func() {
			_, filename, _, _ := runtime.Caller(0)
			So(
				errStr,
				ShouldContainSubstring,
				filename,
			)
		})

		Convey("The error should contain line number", func() {
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-1),
			)
		})

		Convey("The error should be a MyError", func() {
			So(errors.Is(err, &MyError{}), ShouldBeTrue)
		})
	})
}

func TestWrapNested(t *testing.T) {
	Convey("Create a nest-traced error", t, func() {
		var err error
		err = &MyError{}
		Wrap(&err) // -2
		Wrap(&err) // -1
		_, _, line, _ := runtime.Caller(0)

		errStr := err.Error()

		Convey("The error should contain file name twice", func() {
			_, filename, _, _ := runtime.Caller(0)
			So(
				strings.Count(errStr, filename),
				ShouldEqual,
				2,
			)
		})

		Convey("The error should contain line numbers", func() {
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-1),
			)
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-2),
			)
		})
	})
}

func TestAnnotate(t *testing.T) {
	Convey("Create an annotated error", t, func() {
		annotation := "some annotation"
		var err error
		err = &MyError{}
		Wrap(&err, annotation)
		_, _, line, _ := runtime.Caller(0)

		errStr := err.Error()

		Convey("The error should contain file name", func() {
			_, filename, _, _ := runtime.Caller(0)
			So(
				errStr,
				ShouldContainSubstring,
				filename,
			)
		})

		Convey("The error should contain line number", func() {
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-1),
			)
		})

		Convey("The error should contain annotation", func() {
			So(
				errStr,
				ShouldContainSubstring,
				annotation,
			)
		})

		Convey("The error should be a MyError", func() {
			So(errors.Is(err, &MyError{}), ShouldBeTrue)
		})
	})

	Convey("Create an annotated error with fmt.Sprintf", t, func() {
		var err error
		err = &MyError{}
		Wrap(&err, "some annotation %v", "arg")
		errStr := err.Error()
		Convey("The error should contain fmt arg", func() {
			So(errStr, ShouldContainSubstring, "arg")
		})
	})
}

func TestAnnotateNested(t *testing.T) {
	Convey("Create a nest-annotated error", t, func() {
		annotation1 := "some annotation 1"
		annotation2 := "some annotation 2"
		var err error
    err = &MyError{}
		Wrap(&err, annotation1)
		Wrap(&err, annotation2)
		_, _, line, _ := runtime.Caller(0)

		errStr := err.Error()

		Convey("The error should contain file name twice", func() {
			_, filename, _, _ := runtime.Caller(0)
			So(
				strings.Count(errStr, filename),
				ShouldEqual,
				2,
			)
		})

		Convey("The error should contain file name", func() {
			_, filename, _, _ := runtime.Caller(0)
			So(
				errStr,
				ShouldContainSubstring,
				filename,
			)
		})

		Convey("The error should contain line numbers", func() {
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-1),
			)
			So(
				errStr,
				ShouldContainSubstring,
				fmt.Sprintf("%d", line-2),
			)
		})

		Convey(
			"The error should contain annotation",
			func() {
				So(
					errStr, ShouldContainSubstring,
					annotation1,
				)
				So(
					errStr, ShouldContainSubstring,
					annotation2,
				)
			},
		)

		Convey("The error should be a MyError", func() {
			So(errors.Is(err, &MyError{}), ShouldBeTrue)
		})
	})
}

func TestWrapNil(t *testing.T) {
	Convey("Try to trace nil", t, func() {
		var err error
		Wrap(&err)
		Convey("Should get nil", func() {
			So(err, ShouldBeNil)
		})
	})

	Convey("Try to annotate nil", t, func() {
		var err error
		Wrap(&err, "some annotation")
		Convey("Should get nil", func() {
			So(err, ShouldBeNil)
		})
	})
}
