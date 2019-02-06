let foldingFn =
    (acc: Future.t(list('a)), cursor: Future.t('a)): Future.t(list('a)) =>
  Future.flatMap(acc, somelist =>
    Future.map(cursor, someval => List.append(somelist, [someval]))
  );

/*
 * foldFutureList :: list(Future.t('a)) -> Future.t(list('a))
 */
let foldFutureList = (futures: list(Future.t('a))): Future.t(list('a)) => {
  let seed: Future.t(list('a)) = Future.value([]);
  List.fold_left(foldingFn, seed, futures);
};

/* recursive fold */
/*
 * foldRec :: Future.t(list('a) -> list(Future.t('a)) -> Future.t(list('a))
 */
let rec foldRec =
        (acc: Future.t(list('a)), futures: list(Future.t('a)))
        : Future.t(list('a)) => {
  let cursor = List.hd(futures);
  let remaining = List.tl(futures);

  foldRec(
    Future.flatMap(acc, somelist =>
      Future.map(cursor, someval => List.append(somelist, [someval]))
    ),
    remaining,
  );
};
/* recursive fold */
/*
 * foldFutureListRec :: list(Future.t('a)) -> Future.t(list('a))
 */
let foldFutureListRec = (futures: list(Future.t('a))): Future.t(list('a)) => {
  let seed: Future.t(list('a)) = Future.value([]);
  foldRec(seed, futures);
};