package main

import (
	"mysqlStudy/internal/dbObject"
)

func main() {
	//data := dbObject.GetTestTableInfo()
	//dbObject.InsertDataToTest(data[:2])
	//dbObject.UpdateCommitIdById(5, 10)
	//dbObject.DeleteDataById(1)
	dbObject.TransactionTest()
	defer dbObject.Finalizer()

}
