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

describe("Troll Indempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
        QCheck.Test.make(
            ~count=1000,
            ~name="all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
            troll_arbitrary,
            troll => {
            let stableTroll = all_elves_resurrected(troll);
                scoring(stableTroll) == 0;
            }
        ) |> expect.ext.qCheckTest;
      ();
  })
});

describe("Troll Metamorphism", ({test}) => {
  test(
    "i_got_one increase the Troll killing list",
    ({expect}) => {
      QCheck.Test.make(
        ~count=1000,
        ~name="i_got_one increase the Troll killing list",
        troll_elf_arbitrary,
        ((troll, elf)) => {
            scoring(troll) < scoring(i_got_one(elf, troll));
        }
      ) |> expect.ext.qCheckTest;
      ();
  })
});

describe("Troll Injection", ({test}) => {
  test(
    "i_got_one increase the Troll killing list differently",
    ({expect}) => {
      QCheck.Test.make(
        ~count=1000,
        ~name="i_got_one increase the Troll killing list",
        troll_two_elves_arbitrary,
        ((troll, elf1, elf2)) => {
           let kill1 = i_got_one(elf1, troll);
           let kill2 = i_got_one(elf2, kill1);
            scoring(kill1) < scoring(kill2);
        }
      ) |> expect.ext.qCheckTest;
      ();
  })
});