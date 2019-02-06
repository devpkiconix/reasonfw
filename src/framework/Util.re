let mapMaybe = (f: 'a => 'b, maybe: option('a)) =>
  Belt.Option.map(maybe, f);