#!/bin/bash
#判断参数是否为0个
if [ $# == 0 ]; then
  echo "please use ./BatchGenerateFunc.sh [create|delete|main] [args...]"
else
  #记录下所有参数
  args=("$@")
  len=${#args[@]}
  if [ $1 == "create" ]; then
    if [ $# == 1 ]; then
      echo "please use ./BatchGenerateFunc.sh create [要创建的模块名]"
    else
      echo "输入的功能为:${args[0]},参数个数为$(($len - 1))"
      for ((i = 1; i < ${len}; i++)); do
        moduleName=${args[i]}
        moduleName=${moduleName,,}
        echo "------------create ${moduleName} module--------------"
        dir="./internal/${moduleName}Study"
        if [ -d "$dir" ]; then
          echo "$dir Directory already exists"
          continue
        else
          mkdir -p "$dir"
          echo "$dir Directory created"
        fi
        echo "package ${moduleName}Study" >${dir}/${moduleName}Study.go
        echo >>${dir}/${moduleName}Study.go
        for j in {1..10}; do
          echo "// ${moduleName^}Test${j} " >>${dir}/${moduleName}Study.go
          echo "func ${moduleName^}Test${j}(){" >>${dir}/${moduleName}Study.go
          echo >>${dir}/${moduleName}Study.go
          echo "}" >>${dir}/${moduleName}Study.go
          echo >>${dir}/${moduleName}Study.go
        done
        echo "模块${moduleName}创建成功!"
      done
    fi
  elif [ $1 == "delete" ]; then
    if [ $# == 1 ]; then
      echo "please use ./BatchGenerateFunc.sh delete [要删除的模块名]"
    else
      echo "输入的功能为:${args[0]},参数个数为$(($len - 1))"
      for ((i = 1; i < ${#args[@]}; i++)); do
        moduleName=${args[i]}
        moduleName=${moduleName,,}
        rm -r ./internal/${moduleName}Study
        if [ $? == 0 ]; then
          echo "模块${moduleName}删除成功!"
        else
          echo "模块${moduleName}删除失败!"
        fi
      done
    fi
  elif [ $1 == "main" ]; then
    echo "请输入模块名:"
    read -r moduleName
    moduleName=${moduleName,,}
    echo "请输入编号:(如3-->test3)"
    read -r num
    echo "请输入子函数个数:"
    read -r funcNum
    echo "-----------------以下是生成的内容------------------"
    printf "//模块%s\n" ${moduleName}
    printf "func test%s() {\n" ${num}
    for ((i = 1; i <= ${funcNum}; i++)); do
      printf "    %sStudy.%sTest%d()\n" ${moduleName} ${moduleName^} ${i}
    done
    printf "}\n"
  else
    echo "error:Wrong parameter!"
    echo "please use ./BatchGenerateFunc.sh create|delete|main [args...]"
  fi
fi
