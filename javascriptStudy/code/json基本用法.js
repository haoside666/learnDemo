var stus = [
    {
        "id": 1001,
        "name": "唐伯虎",
        "age": 25
    },
    {
        "id": 1002,
        "name": "秋香",
        "age": 18
    },
    {
        "id": 1003,
        "name": "石榴姐",
        "age": 22
    },
]
// 循环
for (var i = 0; i < stus.length; i++) {
    // console.log(stus[i]);
    for (var key in stus[i]) {
        console.log(key + '=' + stus[i][key]);
    }
}

/**
 *  将JSON对象转换为字符串
 */
var stu={
    "id":1001,
    "name":"tom",
    "age":18
}
console.log(typeof stu,stu);

var str=JSON.stringify(stu);
console.log(typeof str,str);


/**
 *  将字符串转换为JSON对象
 */
str='{"id":1001,"name":"tom","age":18}';
console.log(typeof str,str);

var obj=JSON.parse(str);
// var obj=eval('('+str+')'); // 不推荐

console.log(typeof obj,obj);
console.log(obj.name);