var stu={
    name:'tom',
    age:18,
    study:function(){
        console.log('我叫'+this.name+'，年龄：'+this.age);
    },
}
stu.study(); // 调用对象的方法

// 定义一个函数
function run(){
    console.log('正在跑步。。。。',this);
}


/**
 *  如果stu想调用run()函数，怎么办？
 */
// 方式1：为stu添加run方法，永久添加
// stu.run=run; // 为stu添加run属性，指向run()函数
// stu.run();

// 方式2：只想临时调用
run.call(stu); // 以stu对象的身份来调用run()函数
run.apply(stu);


/**
 *  this的转变
 */
// window.run(); // 直接调用，此时的this表示window
// run.call(stu); // 对象临时调用，此时的this表示调用的对象，即stu，称为对象冒充
// run.apply(stu);



/**
 *  call和apply的区别
 */
function calc(a,b,c){
    console.log(a+b+c);
}

calc.call(stu,1,2,3); // 逐个传参
calc.apply(stu,[1,2,3]); // 数组形式传参


//作用：以某个对象的身份去调用别人的方法
// 比如：需要改变this的值时
function greet() {
    console.log(`Hello, ${this.name}`);
}

const person = {
    name: 'person',
};

const animal = {
    name: 'animal',
};

greet.call(person)
greet.call(animal)

//示例二: 对象冒充继承，也称为构造继承
//父类对象
function Person(name,age){
    this.name=name;
    this.age=age;
    this.run=function(){
        console.log('正在跑步');
    }
}

Person.prototype.sex='male';
Person.prototype.show=function(){
    console.log('我叫'+this.name+'，年龄：'+this.age+'，性别：'+this.sex);
}

//子类对象
function Student(name,age,score){
    // 此处Person中的this指向的是将来创建的Student对象，所以称为对象冒充
    // 以stu的身份调用person的构造函数
    Person.call(this,name,age);
    this.score=score;
}

stu=new Student('tom',20,98.5);
// 可以继承父类构造函数中的属性和方法
console.log(stu.name,stu.age,stu.score);
stu.run();
// 注意：无法继承父类原型中的属性和方法，需结合原型链