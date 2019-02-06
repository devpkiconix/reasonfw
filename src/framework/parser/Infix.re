/* let (>>=): (t('a), 'a => t('b)) => t('b); */
/* let (<$>): (t('a), 'a => 'b) => t('b); */
let (>>=) = (a: Types.future('a), f: 'a => Types.future('b)) =>
  BsFluture.chain(f, a);
let (<$>) = (a: Types.future('a), f: 'a => 'b) => BsFluture.map(f, a);