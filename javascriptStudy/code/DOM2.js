document.addEventListener("click", function () {
    document.body.innerHTML = document.activeElement;
    var box = document.createElement('div');
    box.id = "myDiv";
    box.innerText = Math.random();

    var btn = document.createElement("button");
    btn.innerText = "按钮";
    // 将按钮的 onclick 属性设置为 myfunction 函数
    btn.setAttribute("onclick", "myfunction()");
    // 采用直接赋值函数引用的方式，在html中看不到onclick属性
    // btn.onclick = myfunction

    document.body.appendChild(box);
    document.body.appendChild(btn);
});
function myfunction() {
    alert(document.title);
}