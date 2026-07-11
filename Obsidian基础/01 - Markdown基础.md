---
tags:
  - Obsidian
  - 教程
  - Markdown
category: Obsidian基础
date: 2026-07-11
---

# Markdown 基础

## 一、标题

使用 `#` 符号表示标题，`#` 的数量对应标题级别：

```markdown
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
```

## 二、段落与换行

- 直接输入文本即为段落
- 段落之间需要空一行
- 要在段落内换行，在行尾添加两个空格 `  `

## 三、列表

### 无序列表

使用 `-`、`*` 或 `+`：

```markdown
- 项目一
- 项目二
  - 子项目一
  - 子项目二
```

### 有序列表

使用数字加 `.`：

```markdown
1. 第一步
2. 第二步
   1. 子步骤一
   2. 子步骤二
```

## 四、强调

```markdown
**粗体文本**
*斜体文本*
***粗斜体文本***
~~删除线文本~~
```

## 五、链接

### 普通链接

```markdown
[链接文本](链接地址)
[百度](https://www.baidu.com)
```

### 引用链接

```markdown
[百度][1]

[1]: https://www.baidu.com
```

## 六、图片

```markdown
![图片描述](图片地址)
![封面](https://example.com/cover.jpg)
```

## 七、代码

### 行内代码

```markdown
`print("Hello World")`
```

### 代码块

使用三个反引号，并指定语言：

```markdown
```python
def hello():
    print("Hello World")
```
```

## 八、引用

```markdown
> 这是一段引用文本
> 
> 引用可以包含多个段落
```

## 九、表格

```markdown
| 姓名 | 年龄 | 职业 |
|------|------|------|
| 张三 | 25   | 工程师 |
| 李四 | 30   | 设计师 |
```

## 十、分割线

```markdown
---
***
___
```

## 十一、任务列表

```markdown
- [x] 已完成任务
- [ ] 未完成任务
- [ ] 待办事项
```

## 十二、脚注

```markdown
这是一段带有脚注的文本[^1]

[^1]: 这是脚注的内容
```

## 十三、高亮

```markdown
==高亮文本==
```

## 十四、数学公式

行内公式：

```markdown
$E=mc^2$
```

块级公式：

```markdown
$$
\sum_{i=1}^{n} i = \frac{n(n+1)}{2}
$$
```

## 十五、HTML 支持

Markdown 支持内嵌 HTML 标签：

```markdown
<span style="color: red;">红色文本</span>
<br>
<hr>
```

## 十六、常用快捷键

- **加粗**：Ctrl/Cmd + B
- **斜体**：Ctrl/Cmd + I
- **链接**：Ctrl/Cmd + K
- **代码块**：Ctrl/Cmd + Shift + C
- **表格**：Ctrl/Cmd + T
- **无序列表**：Ctrl/Cmd + Shift + L
- **有序列表**：Ctrl/Cmd + Shift + O

---
