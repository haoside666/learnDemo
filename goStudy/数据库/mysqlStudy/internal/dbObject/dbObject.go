package dbObject

import (
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"github.com/jmoiron/sqlx"
	. "mysqlStudy/internal/tableObject/testClass"
)

var (
	db *sqlx.DB
)

func init() {
	database, err := sqlx.Connect("mysql", "user:passwd@tcp(127.0.0.1:3306)/test")
	err != nil {
		fmt.Println("连接数据库失败：", err)
		return
	}
	db = database
	fmt.Println("连接数据库成功!")
}

func Finalizer() {
	db.Close()
	fmt.Println("关闭数据库")
}

func GetTestTableInfo() []Test {
	var data []Test
	err := db.Select(&data, "select * from test")
	if err != nil {
		fmt.Println("exec failed, ", err)
		return nil
	}
	return data
}

func InsertDataToTest(records []Test) {
	sql := `insert into test(id,type,commitId,cmdArgv,addition) values (:id, :types, :commitId, :cmdArgv, :addition)`
	db.NamedExec(sql, records)
	// 执行SQL语句插入多条记录
	result, err := db.Exec(sql, records)
	if err != nil {
		fmt.Println(err)
		panic(err)
	} else {
		fmt.Println(result)
	}
}

func UpdateCommitIdById(id int, commitId int) {
	res, err := db.Exec("update test set commitId=? where id=?", commitId, id)
	if err != nil {
		fmt.Println("exec failed, ", err)
		return
	}
	row, err := res.RowsAffected()
	if err != nil {
		fmt.Println("rows failed, ", err)
	}
	fmt.Println("update succ:", row)
}

func DeleteDataById(id int) {
	res, err := db.Exec("delete from test where id=?", id)
	if err != nil {
		fmt.Println("exec failed, ", err)
		return
	}

	row, err := res.RowsAffected()
	if err != nil {
		fmt.Println("rows failed, ", err)
	}

	fmt.Println("delete succ: ", row)
}

func TransactionTest() {
	tx := db.MustBegin()
	result, err := tx.Exec("insert into test(id,type)values(?, ?)", 1, 2)
	if err != nil {
		fmt.Println("exec failed, ", err)
		tx.Rollback()
		return
	}
	row, err := result.RowsAffected()
	if err != nil {
		fmt.Println("rows failed, ", err)
	}
	fmt.Println("insert succ:", row)

	tx.Commit()
}
