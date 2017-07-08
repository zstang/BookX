program island;

const
  MaxInhabitant = 'E'; {��������}
MaxStatement = 100; {���Ի���}

type
  {ö���õ���ֵ����ʹ��ħ�����࣬���죬���ϣ�˵�ѣ���֪������ȷ��}
  TEnum = (Divine, Evil, Human, Day, Night, Lie, Unknown, Undeducible);

  {��¼״̬�����ݽṹ}
  {����KIND(state, speaker)����state.kindʵ�֣�����TIME(state)����state.timeʵ��}
  TState = record
    Kind: array['A' .. MaxInhabitant] of TEnum;  {ÿ����������}
    Time: TEnum;                                 {ʱ��}
  end;

  {��ʽ����¼�Ի������ݽṹ}
  TStatement = record
    Spk: Char; {˵����}
    Sub: Char; {���Ϊ#0��ʱ�򣬶Ի������ǹ���ʱ���}
    Obj: TEnum; {����}
    Neg: Boolean; {�Ƿ���ַ�}
  end;

var
  N: Integer; {�Ի���}
  Statement: array[1 .. MaxStatement] of TStatement; {���еĶԻ�}
  State, Fact: TState; {��ǰ״̬���ܹ��Ƶ���������ʵ}

{�ж�һ�����Ϊkind�ľ�����ʱ��Ϊtimeʱ�Ƿ�˵��}
function Lying(Kind, Time: TEnum): Boolean;
begin
  Lying := (Kind = Evil) or ((Kind = Human) and (Time = Night));
            {ħ�������������ϣ�����˵��}
end;

{�ж϶Ի�statement�Ƿ�����������state}
function Truth(var Statement: TStatement; var State: TState): Boolean;
var
  Res: Boolean;
begin
  if Statement.Sub = #0 then Res := Statement.Obj = State.Time {����ʱ���}
  else if Statement.Obj = Lie then Res := Lying(State.Kind[Statement.Sub], State.Time) {����˵�ѵ�}
  else Res := Statement.Obj = State.Kind[Statement.Sub]; {���ھ������͵�}
  if Statement.Neg then Res := not Res; {���ַ���}
  Truth := Res;
end;

{�����Ի�����ì�ܣ���ȫ����ì����������Ƶ�����ʵ}
procedure Analysis;
var
  I: Integer;
  J: Char;
begin
  for I := 1 to N do   {��һ����ÿһ�仰}
if Lying(State.Kind[Statement[I].Spk], State.Time) xor Truth(Statement[I], State) then
{�Ի�û��ì��}
    else Exit; {��ì�����˳�}
  {�Ի�ȫ����ì�ܣ��������Ƶ�����ʵ}
  if Fact.Time = Unknown then {��һ�����е�״̬��ֱ�Ӽ�¼֮}
    Fact := State
  else begin
    {�����Ѿ����ڵ���ʵ�����������޷�ȷ������ʵ}
    for J := 'A' to MaxInhabitant do
      if Fact.Kind[J] <> State.Kind[J] then Fact.Kind[J] := Undeducible;
                   {�޷�ȷ���ľ������}
if Fact.Time <> State.Time then Fact.Time := Undeducible;
               {ʱ��Ҳ�����޷�ȷ��}
  end;
end;

{�������п��ܵľ������}
procedure TryAll(Now: Char);
begin
  if Now > MaxInhabitant then Analysis  {���о��񶼸�����ݣ�����Խ��з���}
  else begin
    State.Kind[Now] := Divine;   {�������NowΪ��ʹ}
    TryAll(Succ(Now));
    State.Kind[Now] := Evil;     {�������NowΪħ��}
    TryAll(Succ(Now));
    State.Kind[Now] := Human;    {�������NowΪ����}
    TryAll(Succ(Now));
  end;
end;

{����߼������⣬��������}
procedure Solve;
const
  KindStr: array[TEnum] of string   {TEnumÿ��Ԫ�ض�Ӧ���ַ�����ʾ���}
 = ('divine', 'evil', 'human', 'day', 'night', '', '', '');

var
  NoFacts: Boolean;
  I: Char;
begin
  {��ʼ����ʵ}
  for I:='A' to MaxInhabitant do Fact.Kind[I]:=Unknown;
  Fact.Time:=Unknown;
  {ö�����е�״̬}
  State.Time := Day;      {����ʱ��Ϊ����}
  TryAll('A');
  State.Time := Night;    {����ʱ��Ϊ����}
  TryAll('A');
  {�жϿ����Ƶ�����ʵ}
  if Fact.Time = Unknown then {�Ի��������}
Writeln('This is impossible.')
  else begin
    {��������Ƶ�����ʵ}
    NoFacts := True;
    for I := 'A' to MaxInhabitant do   {���ÿ��ȷ���ľ������}
      if Fact.Kind[I] <> Undeducible then
      begin
        Writeln(I, ' is ', KindStr[Fact.Kind[I]], '.');
        NoFacts := False;
      end;
    if Fact.Time <> Undeducible then   {ʱ��ȷ����Ҳ���}
    begin
      Writeln('It is ', KindStr[Fact.Time], '.');
      NoFacts := False;
    end;
    {û���Ƶ����κ���ʵ��}
    if NoFacts then Writeln('No facts are deducible.')
  end;
end;
{�������еĶԻ�������ʽ��}
procedure ReadStatements;
var
  I: Integer;
  S: string;
begin
  Readln(N);  {�����������}
  for I := 1 to N do  {��һ����ͷ���ÿһ�����}
  begin
    Readln(S);      {�������}
    Statement[I].Spk := S[1]; {ȡ��˵����}
    if Copy(S, 4, 2) = 'It' then {����ʱ��ģ���It is ( day | night )��}
    begin
      Statement[I].Sub := #0;
      if Pos('day', S) > 0 then
        Statement[I].Obj := Day
      else
        Statement[I].Obj := Night;
    end
    else begin   {������ݵģ���I am [not]���������ߡ�X is [not]������}
      if S[4] = 'I' then {ȡ������}
        Statement[I].Sub := S[1]
      else
        Statement[I].Sub := S[4];
     {�жϱ���}
      if Pos('divine', S) > 0 then     {����ʹ}
        Statement[I].Obj := Divine
      else if Pos('evil', S) > 0 then     {��ħ��}
        Statement[I].Obj := Evil
      else if Pos('human', S) > 0 then   {������}
        Statement[I].Obj := Human
      else if Pos('lying', S) > 0 then    {��˵��}
        Statement[I].Obj := Lie;
    end;
    {�жϷ񶨵����}
    Statement[I].Neg := Pos('not', S) > 0;
  end;
end;
begin
  Assign(Input, 'island.in');    {ָ����������ļ�}
  Reset(Input);
  Assign(Output, 'island.out');
  Rewrite(Output);
  ReadStatements; {��������}
  Solve; {��Ⲣ������}
  Close(Input); {�ر��ļ�}
  Close(Output); {�ر��ļ�}
end.
