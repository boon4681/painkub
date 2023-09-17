const fs = require("fs")
const child = require("child_process")

const file = fs.readFileSync("../grammar.peggy", "utf8")
let html = `<html lang="en">
<head>
<title>Preview</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=JetBrains+Mono:ital,wght@0,100;0,200;0,300;0,400;0,500;0,600;0,700;0,800;1,100;1,200;1,300;1,400;1,500;1,600;1,700;1,800&family=Noto+Sans+Thai:wght@100;200;300;400;500;600;700;800;900&display=swap');
body {
    display: flex;
    flex-direction: column;
    width: 1000px;
    margin: 0 auto;
    font-family: "JetBrains Mono",sans-serif
}
.block {
    display: flex;
    flex-direction: column;
    margin: 10px
}
img {
    width: 300px
}
g {
    color:#009c00
}
</style>
</head>
<body>`
let map = {}
const lines = file.split("\n")
for (const line of lines) {
    const first_space = line.search(" ")
    const key = line.slice(0, first_space).trim();
    if (key.length > 0) {
        map[key] = line.slice(first_space)
    }
}
for (const key in map) {
    // const done = child.execSync(`peggy-tracks -s ${key} -o ../spec/${key}.svg ../grammar.peggy`)
    // console.log(key, done.toString())
    let used = []
    for (const k in map) {
        if (key === k) continue;
        if (map[k].search(key) > 0) {
            used.push(k)
        }
    }
    html += `<div class="block">
    <span><b id="${key}">${key}</b>: used by ${used.map(a => "<a href='#" + a + "'>" + a + "</a>").join(", ")}</span>
    <span>${map[key].replace(/("[^"]*")/g,"<g>$1</g>")}</span>
<!--    <img src="${key}.svg"  alt="${key}"/>-->
</div>`
}

html += `</body></html>`

fs.writeFileSync("../spec/preview.html", html)