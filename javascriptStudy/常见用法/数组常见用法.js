
var names=['tom','jack','alice','mike','james','lucy'];
console.log(names);

// 1.reverse() 反转
names.reverse();
console.log(names);

// 2.indexOf() 查询指定元素第一次出现的位置
console.log(names.indexOf('jack'));
console.log(names.indexOf('qianqian')); // 如果不存在，则返回-1
console.log(names.indexOf('jack',2)); // 从索引为2的位置开始查找

// 3.lastIndexOf() 查询指定元素最后一次出现的位置
console.log(names.lastIndexOf('jack'));

// 4.join() 拼接为字符串
console.log(names.join()); // 默认使用,逗号拼接
console.log(names.join('-')); // 指定要分隔的字符

// 5.concat() 将多个数组拼接成一个数组
var hobbies=['eat','sleep','doudou'];
names=names.concat(hobbies);
console.log(names);

// 6.push() 向数组末尾添加新的元素，返回新的数组长度
names.push('yang'); // 等价于names[names.length]='yang';
var length=names.push('aaa','bbb','ccc');
console.log(names);
console.log(length);

// 7.pop() 删除并返回数组末尾的元素
console.log(names.pop());

// 8.unshift() 向数组开头添加新的元素，返回新的数组长度
names.unshift('aaa','bbb','ccc');


// 9.shift() 删除并返回数组开头的元素
console.log(names.shift());

// 10.slice() 获取指定索引范围内的元素
console.log(names)
console.log(names.slice(2,4)); // 获取索引为[2,4)之间的元素，左闭右开
console.log(names.slice(2)); // 如果省略第二个参数，表示获取到数组末尾

// 11.splice() 从指定索引位置删除指定个数的元素，并在此位置添加新的元素
var array=names.splice(2,3); // 从索引为2的位置开始删除，删除3个
console.log(array); // 返回被删除的元素
names.splice(2,3,'aaa','bbb'); // 在删除的位置添加元素
names.splice(3,1); // 删除索引为3的元素
console.log(names);

// 12.toString() 将数组转换为字符串
var str=names.toString(); // 等价于names.join()，与没有参数的join()方法相同
console.log(str);

// 13.valueOf() 返回数组本身，会自动调用
console.log(names.valueOf());
console.log(names); // 自动调用valueOf()

// 14.sort() 排序，默认按字符编码ASCII的顺序排列
// names.sort();
var nums=[12,24,21,65,3,27,77];
nums.sort(); // 默认会将数字转换为字符串，然后根据字符编码进行排序
console.log(nums)

/**
 *  自定义比较规则，简单来说，需要为sort()传入一个参数，参数为函数
 *      1.升序
 *          如果a比b大，返回一个正数
 *          如果a比b小，返回一个负数
 *          如果a比b相同，返回0
 *      2.降序
 *          如果a比b大，返回一个负数
 *          如果a比b小，返回一个正数
 *          如果a比b相同，返回0
 */

nums.sort((a,b)=>{return a-b});
console.log(nums)


// 15.forEach() 遍历数组
names.forEach(function(value,index){ // value表示数组元素值，index表示元素索引
    console.log(value,index);
});