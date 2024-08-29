
#let counter = state("count", 0)

#let fNumber() = {
  counter.update(count => count + 1)
  context counter.get()
}

#let f(title) = {
  [= Number #fNumber()
  content for #title \ \ \ ]
}

#show outline: it => {
  //strong(it)
  it
}

#outline(
  title: [List of content],
)

#f("function A")
#f("function B")
#f("function C")
#f("function D")
#f("function E")
