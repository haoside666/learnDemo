/**
 *  对象的类型
 */
function Student(){}
function Teacher(){}

var obj1=new Object();
var obj2=new Array();
var obj3=new Student();
var obj4=new Teacher();

// typeof只能判断简单的数据类型，判断对象的类型时总是返回object
console.log(typeof obj1); // object
console.log(typeof obj2);
console.log(typeof obj3);
console.log(typeof obj4);

// instanceof用来判断对象的类型，判断对象是否为某种类型，返回boolean值
console.log(obj1 instanceof Object); //false
console.log(obj2 instanceof Array);
console.log(obj3 instanceof Student);
console.log(obj4 instanceof Teacher);
// 结论：构造函数的名称就是对象的类型名

// if(obj3 instanceof Student){

// }


/**
 *  constructor属性
 */
console.log(obj3.constructor);  // 通过调用对象的constructor属性，可以获取到对象的构造函数
console.log(obj3.constructor==Student);
console.log(obj3);

console.log(obj3.constructor.name); // 通过调用构造函数的name属性，获取构造函数的名称，即对象的类型名
console.log(obj4.constructor.name);