package template_method

import "fmt"

type Downloader interface {
	Download(uri string)
}

type implement interface {
	download()
	save()
}

type template struct {
	impl implement
	uri  string
}

func newTemplate(impl implement) *template {
	return &template{
		impl: impl,
	}
}

func (t *template) Download(uri string) {
	t.uri = uri
	fmt.Print("prepare downloading\n")
	t.impl.download()
	t.impl.save()
	fmt.Print("finish downloading\n")
}

type HTTPDownloader struct {
	*template
}

func NewHTTPDownloader() Downloader {
	downloader := &HTTPDownloader{}
	downloader.template = newTemplate(downloader)
	return downloader
}

func (d *HTTPDownloader) download() {
	fmt.Printf("download %s via http\n", d.uri)
}

func (*HTTPDownloader) save() {
	fmt.Printf("http save\n")
}

type FTPDownloader struct {
	*template
}

func NewFTPDownloader() Downloader {
	downloader := &FTPDownloader{}
	downloader.template = newTemplate(downloader)
	return downloader
}

func (d *FTPDownloader) download() {
	fmt.Printf("download %s via ftp\n", d.uri)
}

func (*FTPDownloader) save() {
	fmt.Printf("ftp save\n")
}

// ---------------------------------------测试--------------------------------------
func ExampleHTTPDownloader() {
	var downloader1 = NewHTTPDownloader()

	downloader1.Download("http://example.com/abc.zip")
}

func ExampleFTPDownloader() {
	var downloader2 = NewFTPDownloader()

	downloader2.Download("ftp://example.com/abc.zip")
}

func Test() {
	ExampleHTTPDownloader()
	ExampleFTPDownloader()
}
