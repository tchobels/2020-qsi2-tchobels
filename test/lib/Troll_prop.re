open Framework;
open QCheckRely;
open Generator.Fantasy;
open Lib.Troll;

let {describe} = extendDescribe(QCheckRely.Matchers.matchers);

describe("Troll Invariance", ({test}) => {
  test("Troll score should be 0 when all elves resurrected", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_arbitrary,
      troll =>
      all_elves_resurrected(troll) |> scoring == 0
    )
    |> expect.ext.qCheckTest;
    ();
  });
  test("Troll score should always be >= 0", ({expect}) => {
    QCheck.Test.make(
          ~count=1000,
          ~name="Troll score should always be >= 0",
          troll_arbitrary,
          troll => scoring(troll) >= 0
        )
        |> expect.ext.qCheckTest;
        ();
    ()
  });
});

describe("Troll Inverse", ({test}) => {
  test("oops_he_survived should always be inverse of i_got_one", ({expect}) => {
    QCheck.Test.make(
          ~count=1000,
          ~name="Kill an elf and elf finally survived never changed the scoring",
          troll_elf_arbitrary,
          ((troll,elf)) => i_got_one(elf,troll) |> oops_he_survived(elf) |> scoring == scoring(troll)
        )
        |> expect.ext.qCheckTest;
        ();
    ()
  })
});

describe("Troll Analogy", ({test}) => {
  test("i_got_one and i_got should be consistent", ({expect}) => {
    /* Test go there */
    QCheck.Test.make(
              ~count=1000,
              ~name="",
              troll_elf_int_arbitrary,
              ((troll,elf, qty)) => (List.init(qty, _ => 1) |> List.fold_left((cur_troll, _ ) => i_got_one(elf, cur_troll), troll)  |> scoring) == (i_got(qty, elf, troll) |> scoring)
            )
            |> expect.ext.qCheckTest;
            ();
        ()
  })
});

describe("Troll Idempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
    /* Test go there */
    ()
  })
});