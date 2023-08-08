package testClass

type Test struct {
	Id       int    `db:"id"`
	Types    int    `db:"types"`
	CommitId int    `db:"commitId"`
	CmdArgv  string `db:"cmdArgv"`
	Addition string `db:"addition"`
}
