var _ = require('underscore');

function existy(x) { return x != null };
function truthy(x) { return (x != false) && existy(x) };

function cat() {
  var head = _.first(arguments);
  if (existy(head)) {
    return head.concat.apply(head, _.rest(arguments));
  } else
    return [];
}

console.log(cat([1,2,3], [4,5], [6,7,8]));

function construct(head, tail) {
  return cat ([head], _.toArray(tail));
}

console.log(construct(42, [1,2,3]));

function mapcat(fun, coll) {
  return cat.apply(null, _.map(coll, fun));
}

var r = mapcat(function(e) {
  return construct(e, [","]);
}, [1,2,3]);

console.log(r);

function butLast(coll) {
  return _.toArray(coll).slice(0, -1);
}

function interpose(inter, coll) {
  return butLast(mapcat(function(e) {
    return construct(e, [inter]);
  },
  coll));
}

console.log(interpose(',', [1,2,3]));

var zombie = {name: 'Bub', film: 'Day of the Dead'};

console.log(_.pairs(zombie));

r = _.object(_.map(_.pairs(zombie), function(pair) {
  return [pair[0].toUpperCase(), pair[1]];
}));

console.log(r);

var library = [
  {title: 'SICP', isbn: 0262010771, ed:1},
  {title: 'SICP', isbn: 0262510871, ed:2},
  {title: 'Joy of Clojure', isbn: 1935182641, ed:1}
];

console.log(_.pluck(library, 'title'));

function project(table, keys) {
  return _.map(table, function(obj) {
    //return _.pick.apply(null, construct(obj, keys));
    // not sure why they just don't use the following
    return _.pick(obj, keys);
  });
};

console.log(project(library, ['title', 'isbn']));

function rename(obj, newNames) {
  return _.reduce(newNames, function(o, nu, old) {
    if (_.has(obj, old)) {
      o[nu] = obj[old];
      return o;
    }
    else
      return o;
  },
  _.omit.apply(null, construct(obj, _.keys(newNames))));
};

console.log('rename', rename({a: 1, b: 2}, {'a': 'AAA'}));

function as(table, newNames) {
  return _.map(table, function(obj) {
    return rename(obj, newNames);
  });
};

console.log('as', as(library, {ed: 'edition'}));

console.log(project(as(library, {ed: 'edition'}), ['edition']));

function restrict(table, pred) {
  return _.reduce(table, (newTable, obj) => {
    if (truthy(pred(obj)))
      return newTable;
    else
      return _.without(newTable, obj);
  }, table);
};

r = restrict(library, (book) => {
  return book.ed > 1;
});

console.log('restrict', r);

