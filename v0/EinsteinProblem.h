#define PERM_T char*
#define PERM_T_PFLAG "%s"

#include "Perm.h" 
#include <stdio.h>
#include <assert.h>
#include <time.h>

typedef char* str;

str cores[] = {"Vermelho", "Verde", "Amarelo", "Azul", "Branco"};
str bebidas[] = {"Agua", "Cerveja", "Cha", "Cafe", "Leite"};
str cigarros[] = {"PallHall", "Dunhill", "BlueMaster", "Prince", "Blend"};
str animais[] = {"Cachorro", "Gato", "Cavalo", "Zebra", "Passaro"};
str nacionalidades[] = {"Noruegues", "Ingles", "Dinamarques", "Sueco", "Alemao"};

int streq(str x, str y) {
  while (*x && *y) {
    if (*x != *y)
      return 0;
    x += 1;
    y += 1;
  }
  return *x == *y;
}

int sindex(Perm *p, str elem) {
  for (int i = 0; i < 5; i++)
    if (streq(p->data[i], elem))
      return i;
  
  assert(0);
  return -1;
}

int esquerda(int x, int y) {
  return x + 1 == y;
}
int lado(int x, int y) {
  return esquerda(x, y) || esquerda(y, x);
}

int ingles_vermelho(
  Perm *cs, Perm *ns) {
  return sindex(cs, "Vermelho")
    == sindex(ns, "Ingles");
}
int sueco_cachorro(
  Perm *ns, Perm *ms) {
  return sindex(ns, "Sueco")
    == sindex(ms, "Cachorro");
}
int dinamarques_cha(
  Perm *ns, Perm *bs) {
  return sindex(bs, "Cha")
    == sindex(ns, "Dinamarques");
}
int verde_cafe(
  Perm *cs, Perm *bs) {
  return sindex(bs, "Cafe")
    == sindex(cs, "Verde");
}
int pallhall_passaro(
  Perm *gs, Perm *ms) {
  return sindex(gs, "PallHall")
    == sindex(ms, "Passaro");
}
int amarelo_dunhill(
  Perm *cs, Perm *gs) {
  return sindex(cs, "Amarelo")
    == sindex(gs, "Dunhill");
}
int bluemaster_cerveja(
  Perm *gs, Perm *bs) {
  return sindex(bs, "Cerveja")
    == sindex(gs, "BlueMaster");
}
int alemao_prince(
  Perm *ns, Perm *gs) {
  return sindex(ns, "Alemao")
    == sindex(gs, "Prince");
}

int meio_leite(Perm *bs) {
  return sindex(bs, "Leite") == 2;
}
int primeiro_noruegues(Perm *ns) {
  return sindex(ns, "Noruegues") == 0;
}
int verde_esq_branco(Perm *cs) {
  return esquerda(
    sindex(cs, "Verde"),
    sindex(cs, "Branco")
  );
}

int blend_lado_gato(
  Perm *gs, Perm *ms) {
  return lado(
    sindex(gs, "Blend"),
    sindex(ms, "Gato")
  );
}
int dunhill_lado_cavalo(
  Perm *gs, Perm *ms) {
  return lado(
    sindex(gs, "Dunhill"),
    sindex(ms, "Cavalo")
  );
}
int azul_lado_noruegues(
  Perm *cs, Perm *ns) {
  return lado(
    sindex(cs, "Azul"),
    sindex(ns, "Noruegues")
  );
}
int blend_lado_agua(
  Perm *gs, Perm *bs) {
  return lado(
    sindex(gs, "Blend"),
    sindex(bs, "Agua")
  );
}

int count = 0;
void n5(Perm *cs, Perm *ns,
  Perm *gs, Perm *ms, Perm *bs) {
  if (!meio_leite(bs)
    || !dinamarques_cha(ns, bs)
    || !verde_cafe(cs, bs)
    || !bluemaster_cerveja(gs, bs)
    || !blend_lado_agua(gs, bs))
    return;

  printf("%d\n", count++);
  for (int i = 0; i < 5; i++) {
    printf("%s, %s, %s, %s, %s\n",
      cs->data[i], ns->data[i],
      gs->data[i], ms->data[i],
      bs->data[i]);
  }
  printf("\n");
}

void n4(Perm *cs, Perm *ns,
  Perm *gs, Perm *ms) {
  if (!sueco_cachorro(ns, ms)
    || !pallhall_passaro(gs, ms)
    || !blend_lado_gato(gs, ms)
    || !dunhill_lado_cavalo(gs, ms))
    return;

  Perm bs = perm(bebidas, 5);
  while (!completed_perm(&bs)) {
    n5(cs, ns, gs, ms, &bs);
    next_perm_mut(&bs);
  }
  clear_perm(&bs);
}

void n3(Perm *cs, Perm *ns, Perm *gs) {
  if (!amarelo_dunhill(cs, gs)
    || !alemao_prince(ns, gs))
    return;

  Perm ms = perm(animais, 5);
  while (!completed_perm(&ms)) {
    n4(cs, ns, gs, &ms);
    next_perm_mut(&ms);
  }
  clear_perm(&ms);
}

void n2(Perm *cs, Perm *ns) {
  if (!primeiro_noruegues(ns)
    || !ingles_vermelho(cs, ns)
    || !azul_lado_noruegues(cs, ns))
    return;

  Perm gs = perm(cigarros, 5);
  while (!completed_perm(&gs)) {
    n3(cs, ns, &gs);
    next_perm_mut(&gs);
  }
  clear_perm(&gs);
}

void n1(Perm* cs) {
  if (!verde_esq_branco(cs))
    return;
  
  Perm ns = perm(nacionalidades, 5);
  while (!completed_perm(&ns)) {
    n2(cs, &ns);
    next_perm_mut(&ns);
  }
  clear_perm(&ns);
}

int einstein_problem() {
  clock_t begin = clock();

  Perm cs = perm(cores, 5);
  while (!completed_perm(&cs)) {
    n1(&cs);
    next_perm_mut(&cs);
  }
  clear_perm(&cs);
  
  clock_t end = clock();
  double time_spent =
    (double)(end - begin)
    / CLOCKS_PER_SEC;
  
  printf("%f seconds\n", time_spent);
  return 0;
}