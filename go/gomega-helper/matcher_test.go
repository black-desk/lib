package gomegahelper_test

import (
	"fmt"
	"os"
	"testing"

	. "github.com/black-desk/lib/go/ginkgo-helper"
	"github.com/google/uuid"
	. "github.com/onsi/ginkgo/v2"
	. "github.com/onsi/gomega"
)

func TestHelper(t *testing.T) {
	RegisterFailHandler(Fail)
	RunSpecs(t, "ginkgo helper Suite")
}

var _ = Describe("ginkgo helper", func() {
	ContextTable("Given a file path %v", func(resultMsg string, path string, expectErr error) {
		var (
			file *os.File
			err  error
		)
		BeforeEach(func() {
			By("open that file", func() {
				file, err = os.Open(path)
				defer file.Close()
			})
		})
		It(fmt.Sprintf("should be %s", resultMsg), func() {
			if expectErr == nil {
				Expect(err).To(Succeed())
			} else {
				Expect(err).To(MatchError(expectErr))
			}
		})
	},
		ContextTableEntry("found",
			"./matcher_test.go", nil,
		).WithFmt("./matcher_test.go"),
		ContextTableEntry("not found",
			"/some/random/path/"+uuid.NewString(), os.ErrNotExist,
		).WithFmt("/some/random/path/..."),
	)
})
