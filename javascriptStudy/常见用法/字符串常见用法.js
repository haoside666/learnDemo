/**
 *  定义字符串的两种方式
 */
// 1.字符串字面量
// var str='welcome'; // 基本数据类型
// console.log(typeof str);

// 2.使用String构造函数
// var str=new String('i love you'); // 引用数据类型
// console.log(typeof str);

// length属性，用来获取字符串的长度
// console.log(str.length);


/**
 *  常用方法
 */
var str='123454321';

// 1.charAt() 获取指定索引位置的字符
console.log(str.charAt(1)); // 索引从0开始
console.log(str.charAt(str.length-1)); // 获取最后一个字符
console.log(str.charAt(18)); // 如果找不到，返回空字符串
console.log(str[0]); // 等价于str.charAt(0)
console.log(str[str.length-1]);
console.log("------------------charAt----------------------");

// 2.charCodeAt() 获取指定索引位置字符的unicode编码
console.log(str.charCodeAt(1));
console.log("------------------charCodeAt----------------------");

// 3.indexOf() 查找指定的子串在字符串第一次出现的索引位置
console.log(str.indexOf('2'));
console.log(str.indexOf('6')); // 如果找不到，返回-1
console.log(str.indexOf('1',1)); // 从索引为1的位置开始向后查找，默认从头开始查找
console.log("------------------indexOf----------------------");

// 4.lastIndexOf() 查找指定的子串在字符串最后一次出现的索引位置
console.log(str.lastIndexOf('1'));
console.log("------------------lastIndexOf----------------------");

// 5.toLowerCase()、toUpperCase() 转换为小写/大写
// console.log(str.toLowerCase()); // 返回新字符串
// console.log(str.toUpperCase());
// console.log(str); // 原字符串内容不变

// 6.substr() 截取指定长度的字符
// console.log(str.substr(2,3));
// console.log(str.substr(2)); // 如果省略第二个参数，表示截取到末尾
// console.log(str.substr(-5));  // 支持负数，表示从倒数第几个开始截取
// console.log(str.substr(-5,2));

// 7.substring() 截取指定索引范围内的字符
console.log(str.substring(2,3)); // 截取索引为[2,3)之间的字符，左闭右开
console.log(str.substring(2)); // 如果省略第二个参数，表示截取到末尾
console.log(str.substring(-5)); // 不支持负数，会从头开始截取
console.log(str.substring(-5,2));
console.log(str.substring(5,2)); // 具有自动交换能力，等价于str.substring(2,5)
console.log("-------------------substring---------------------");

// 8.slice() 截取指定索引范围内的字符
console.log(str.slice(2,3));
console.log(str.slice(2));
console.log(str.slice(-1)); // 支持负数，表示从倒数第几个开始截取
console.log("-------------------slice---------------------");

// 9.split() 将字符串分割为数组
console.log(str.split(' ')); // 以空格进行拆分
console.log(str.split('')); // 每字符拆分
console.log(str.split(' ',2)); // 第一个参数表示拆分的依据，第二个参数表示拆分后返回的数量
console.log("-------------------split---------------------");

// 10.trim() 去除字符串首尾空格
str="  1212 "
console.log(str,str.length);
str=str.trim()
console.log(str,str.length);

console.log("-------------------trim---------------------");

// 11.fromCharCode() 将字符编码转换为字符串
console.log(String.fromCharCode(97));
console.log(String.fromCharCode(65));
console.log("-------------------fromCharCode---------------------");