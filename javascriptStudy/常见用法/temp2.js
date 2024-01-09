

function getHtmlPlainText(html_str){
    // 创建一个虚拟的HTML元素
    let tempElement = document.createElement('div');
    // 将HTML字符串赋值给元素的innerHTML属性
    tempElement.innerHTML = html_str;
    // 提取所有文本内容
    let allText = tempElement.innerText;
    console.log(allText);
    return allText;
}
html_str=`<div class="container"><div class="line number1 index0 alt2"><code class="js keyword">function</code> <code class="js plain">Parent() {</code></div><div class="line number2 index1 alt1"><code class="js spaces">&nbsp;&nbsp;</code><code class="js keyword">this</code><code class="js plain">.property = </code><code class="js string">"parentProperty"</code><code class="js plain">;</code></div><div class="line number3 index2 alt2"><code class="js plain">}</code></div><div class="line number4 index3 alt1"><code class="js plain">Parent.prototype.say = </code><code class="js keyword">function</code> <code class="js plain">() {</code></div><div class="line number5 index4 alt2"><code class="js spaces">&nbsp;&nbsp;</code><code class="js plain">console.log(</code><code class="js string">"Parent say"</code><code class="js plain">);</code></div><div class="line number6 index5 alt1"><code class="js plain">};</code></div><div class="line number7 index6 alt2"><code class="js keyword">function</code> <code class="js plain">Child() {</code></div><div class="line number8 index7 alt1"><code class="js spaces">&nbsp;&nbsp;</code><code class="js keyword">this</code><code class="js plain">.childProperty = </code><code class="js string">"childProperty"</code><code class="js plain">;</code></div><div class="line number9 index8 alt2"><code class="js plain">}</code></div><div class="line number10 index9 alt1"><code class="js comments">// 修改 Child 的 prototype 属性指向 Parent 实例对象，那么 Child 实例对象的 __proto__ 就会指向其构造函数 Child 的 prototype 属性（即Parent 实例对象）</code></div><div class="line number11 index10 alt2"><code class="js comments">// 修改了 Child.prototype 的指向后，那么原来 Child.prototype 指向的对象由于被没有引用，就会被回收。</code></div><div class="line number12 index11 alt1"><code class="js plain">Child.prototype = </code><code class="js keyword">new</code> <code class="js plain">Parent();</code></div><div class="line number13 index12 alt2"><code class="js plain">const childInstance = </code><code class="js keyword">new</code> <code class="js plain">Child();</code></div><div class="line number14 index13 alt1"><code class="js plain">console.log(childInstance.property); </code><code class="js comments">// 输出 'parentProperty'</code></div><div class="line number15 index14 alt2"><code class="js plain">childInstance.say();</code></div></div>`;
// console.log(html_str)
console.log(getHtmlPlainText(html_str));