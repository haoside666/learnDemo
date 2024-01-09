function Person(name, age) {
    this.name = name;
    this.age = age;
    this.run = function () {
        console.log('正在跑步');
    }
}

Person.prototype.sex = 'male';
Person.prototype.show = function () {
    console.log('我叫' + this.name + '，年龄：' + this.age + '，性别：' + this.sex);
}


/**
 *  方式1：对象冒充继承，也称为构造继承
 */
// function Student(name,age){
//     Person.call(this,name,age); // 此处Person中的this指向的是将来创建的Student对象，所以称为对象冒充
// }
//
// var stu=new Student('tom',20);
// // 可以继承父类构造函数中的属性和方法
// console.log(stu.name,stu.age);
// stu.run();
// 无法继承父类原型中的属性和方法
// console.log(stu.sex);
// stu.show();


/**
 *  方式2：原型链继承
 */
// function Student(name, age) {
//     this.name = name;
//     this.age = age;
//     this.run = function () {
//         console.log('正在跑步');
//     }
// }
//
// Student.prototype = new Person(); // 将Student原型指向Person对象，从而继承Person
// console.log(Student.prototype);
//
// var stu = new Student('tom', 20);
// console.log(stu.name, stu.age); // name和age属性都是undefined
// stu.run();
// console.log(stu.sex);
// stu.show();


/**
 *  方式3：组合继承（对象冒充+原型链）
 */
function Student(name,age){
    Person.call(this,name,age); // 对象冒充
}
// Student.prototype=new Person();  // 方式3.1：调用了两次父类构造函数，生成了两份实例（子类实例将子类原型上的那份屏蔽了，所以性能稍差一点）
Student.prototype=Person.prototype; // 方式3.2：将Student原型指向Person原型


console.log(Student.prototype.constructor); // 输出：[Function: Person], 即是 Parent 构造函数，这是由于 Child.prototype 自身没有，就会沿着 __proto__ 寻找，因此找到 Parent。这明显是不对的
console.log(Student.prototype.constructor === Student); // 输出：false, 这明显也是不对的
// 注意：修改其原型对象之后，同时必须得修改 constructor 的指向
Student.prototype.constructor = Student;

console.log(Student.prototype.constructor);

var stu=new Student('tom',20);
console.log(stu);
console.log(stu.name,stu.age);
stu.run();

console.log(stu.sex);
stu.show();