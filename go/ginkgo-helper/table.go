package ginkgohelper

import (
	"fmt"
	"reflect"

	"github.com/onsi/ginkgo/v2"
)

type entry struct {
	fmtArgs []any
	args    []reflect.Value
}

func ContextTable(message string, fn any, entries ...*entry) {
	for i := range entries {
		ginkgo.Context(fmt.Sprintf(message, entries[i].fmtArgs...), func() {
			vfn := reflect.ValueOf(fn)
			vfn.Call(entries[i].args)
		})
	}
}

func (c *entry) WithFmt(args ...any) *entry {
	c.fmtArgs = args
	return c
}

func ContextEntry(args ...any) *entry {
	ret := &entry{}
	for i := range args {
		ret.args = append(ret.args, reflect.ValueOf(args[i]))
	}
	ret.fmtArgs = args
	return ret
}
