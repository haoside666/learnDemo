package familyAccount

import (
	"fmt"
	"os"
)

type faBasic struct {
	accountType  bool
	accountMoney float64
	changeMoney  float64
	describe     string
}

func (fa faBasic) printFaBasicInfo() {
	if fa.accountType {
		fmt.Printf("收入\t\t%f\t\t%f\t\t%s\n", fa.accountMoney, fa.changeMoney, fa.describe)
	} else {
		fmt.Printf("支出\t\t%f\t\t%f\t\t%s\n", fa.accountMoney, fa.changeMoney, fa.describe)
	}

}

type familyAccount struct {
	records []faBasic
}

func (fa *familyAccount) printInfo() {
	if len(fa.records) == 0 {
		fmt.Println("当前没有收支明细... 来一笔吧!")
		return
	}
	fmt.Printf("收支\t\t账户金额\t\t\t收支金额\t\t说  明\n")
	for _, record := range fa.records {
		record.printFaBasicInfo()
	}
}

func (fa *familyAccount) addInfo(accountType bool, changeMoney float64, describe string) {
	if changeMoney <= 0 {
		fmt.Println("金额必须为正数!!!")
		return
	}
	record := &faBasic{
		accountType: accountType,
		changeMoney: changeMoney,
		describe:    describe,
	}
	length := len(fa.records)
	if length == 0 && accountType == false {
		fmt.Println("当前账户余额为0,无法支出!")
		return
	}
	if length != 0 {
		record.accountMoney = fa.records[length-1].accountMoney
	} else {
		record.accountMoney = 0
	}

	if accountType {
		record.accountMoney += record.changeMoney
	} else {
		if record.accountMoney < record.changeMoney {
			fmt.Println("余额的金额不足")
			return
		} else {
			record.accountMoney -= record.changeMoney
		}
	}
	fa.records = append(fa.records, *record)
}

func menu() {
	fmt.Println("-----------------家庭收支记账软件-----------------")
	fmt.Println("                  1.收支明细")
	fmt.Println("                  2.登记收入")
	fmt.Println("                  3.登记支出")
	fmt.Println("                  4.退 出 ")
	fmt.Print("请选择(1-4):")
}

func FamilyAccountTest() {
	var fa = new(familyAccount)
	option := 0
	for {
		menu()
		fmt.Scanln(&option)
		var money float64
		var note string
		var accountType bool
		switch option {
		case 1:
			fmt.Println("-----------------当前收支明细记录-----------------")
			fa.printInfo()
		case 2:
			accountType = true
			fmt.Println("本次收入金额:")
			fmt.Scanln(&money)
			fmt.Println("本次收入说明:")
			fmt.Scanln(&note)
			fa.addInfo(accountType, money, note)
		case 3:
			accountType = false
			fmt.Println("本次支出金额:")
			fmt.Scanln(&money)
			fmt.Println("本次支出说明:")
			fmt.Scanln(&note)
			fa.addInfo(accountType, money, note)
		case 4:
			os.Exit(1)
		default:
			fmt.Println("请输入正确的选项..")
		}

	}
}
