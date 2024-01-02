document.addEventListener("click", function () {
    // document.activeElement 返回当前获取焦点的元素 
    // innerHTML可以设置指定 HTML 标签中的内容，在这里是设置body标签中的内容为当前获取焦点的元素
    document.body.innerHTML = document.activeElement;
    // document.createElement()	创建一个元素节点
    var box = document.createElement('div');
    document.body.appendChild(box);
    // document.createAttribute()	为指定标签添加一个属性节点
    var att = document.createAttribute('id');
    att.value = "myDiv";
    // document.getElementsByTagName() 返回具有指定标签名的对象集合
    document.getElementsByTagName('div')[0].setAttributeNode(att);
    document.getElementById("myDiv").innerHTML = Math.random();
    var btn = document.createElement("button");
    var t = document.createTextNode("按钮");
    btn.appendChild(t);
    document.body.appendChild(btn);
    var att = document.createAttribute('onclick');
    att.value = "myfunction()";
    document.getElementsByTagName('button')[0].setAttributeNode(att);
});
function myfunction() {
    alert(document.title);
}