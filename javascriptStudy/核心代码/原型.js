function Student(name,age){
    this.name=name; // 实例属性，每个实例都具有一个独立的该属性
    this.age=age;
    this.show=function(){ // 实例方法，每个实例都具有一个独立的该方法
        console.log('我叫'+this.name+'，年龄：'+this.age);
    }
}

// 构造函数中存在一个名为prototype的属性
console.log(Student.prototype);

// 通过为构造函数的prototype添加属性和方法，从而让所有该构造函数创建的对象都能共享这些属性和方法
Student.prototype.sayHello=function(){ // 原型方法
    console.log('您好！');
}
Student.prototype.sayGoodbye=function(){
    console.log('再见！');
}
Student.prototype.class='三年二班'; // 原型属性，为所有对象所共享

console.log(Student.prototype);
// 创建对象
var stu1=new Student('tom',25);
stu1.class='三年一班'; // 为stu1添加一个实例属性class
console.log(stu1.name,stu1.age,stu1.class);
stu1.show();
stu1.sayHello();
stu1.sayGoodbye();
console.log('--------------------------------');

var stu2=new Student('alice',22);
console.log(stu2.name,stu2.age,stu2.class);
stu2.show();
stu2.sayHello();
stu2.sayGoodbye();

function aaa(){
    console.log("test")
}
console.log(aaa.prototype)