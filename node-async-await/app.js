function timeout(ms) {
  return new Promise((res) => setTimeout(res, ms));
}

async function f() {
  console.log(1);
  await timeout(1000);
  console.log(2);
  await timeout(1000);
  console.log(3);
}

f()

