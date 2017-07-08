{ Sample program for "Pushing Boxes"(ZSUCPC2001) }
const
  Max=20; {�ֿⳤ�Ϳ�����ά��}
  Dx: array[1..4] of ShortInt = (-1, 0, 1, 0); {X����ƫ����}
  Dy: array[1..4] of ShortInt = (0, 1, 0, -1); {Y����ƫ����}
  DName: array[1..4] of Char = 'nesw'; {��������}
type
  TNode = record {״̬�������}
            X, Y, D: ShortInt; {(X,Y)=�������꣬D=����㵽(X,Y)����С����}
            From: Word; {���Ǹ������չ����}
          end;
  TMaze = array[1..Max, 1..Max] of Char; {�ֿ��ͼ����}
var
  r, c, SX, SY, BX, BY, TX, TY: ShortInt; {r,c=�ֿ�ĳ��Ϳ�(SX,SY)=����ʼ���꣬(BX,BY)=������ʼ���꣬(TX,TY)=����Ŀ������}
  Closed, Open: Word; {Closed���Open��ָ��}
  Maze, G: TMaze; {Maze=�ֿ��ͼ��G=��ʱ��ͼ}
{Maze[i, j] = '.'��ʾ�ֿ��ͼ������(i, j)���ǿո�}
{Maze[i, j] = '#'��ʾ�ֿ��ͼ������(i, j)����ǽ��}
  Mark: array[1..Max, 1..Max, 1..4] of Boolean; {��־���飬Mark[x,y,k]=True��ʾ������(x,y)�����k���������Ƶ��ڽ��ķ�����}
  List: array[1..Max*Max*4] of TNode; {״̬����}

function Valid(X, Y: ShortInt):Boolean; {������(X,Y)�Ƿ����}
begin
  Valid := (X >= 1) and (X <= r) and (Y >= 1) and (Y <= c);
end;

procedure InputMaze; {����ֿ��ͼ������Ԥ����}
var
  i, j, k:Byte;
begin
  Readln(r, c); {����ֿ�ĳ��Ϳ�}
  for i := 1 to r do
  begin
    for j := 1 to c do
    begin
      Read(Maze[i, j]);
      case Maze[i, j] of {ȷ�����˺����ӵģ���ʼ��Ŀ������}
        'S': begin SX := i; SY := j end;
        'B': begin BX := i; BY := j end;
        'T': begin TX := i; TY := j end;
      end;
      {���Maze[i, j]����ǽ�ڣ�����Maze[i, j]�ǿո�}
      if Maze[i, j] <> '#' then Maze[i, j] := '.';
    end;
    Readln;
  end;
  for i := 1 to r do {Ԥ��������Mark��־����}
  for j := 1 to c do
    if Maze[i, j] = '#' then FillChar(Mark[i, j], SizeOf(Mark[i, j]), False)
    else for k := 1 to 2 do
      if Valid(i-Dx[k], j-Dy[k]) and Valid(i+Dx[k], j+Dy[k]) then
        begin Mark[i, j, k] := True; Mark[i, j, k+2] := True end
      else
        begin Mark[i, j, k] := False; Mark[i, j, k+2] := False end;
end;

procedure DFS(i, j: ShortInt); {�����������}
var
  k:Byte;
begin
  G[i, j] := 'Y'; {��ǡ����ʹ���}
  for k := 1 to 4 do {���ڽӵ�δ���ʹ��������֮}
    if Valid(i+Dx[k], j+Dy[k]) and (G[i+Dx[k], j+Dy[k]]='.') then
      DFS(i+Dx[k], j+Dy[k]);
end;

procedure Expand(SX, SY, BX, BY: ShortInt); {��������������ж��˿ɴ�ĵ�}
begin
  G := Maze; {������ʱ�ֿ��ͼ}
  G[BX, BY] := 'B'; {�������λ��}
  DFS(SX, SY); {���˵ĵ�ǰλ�ÿ�ʼ��������������ж��˿ɴ�ĵ�}
end;

{Ѱ�Ҵ�(X1,Y1)��(X2,Y2)���ߵ����·������λ����(BX,BY)}
procedure PrintWalk(X1, Y1, X2, Y2, BX, BY: ShortInt);
var
  Q: array[1..Max*Max] of TNode; {������������Ķ���}
  Head, Tail: Word; {����ͷβָ��}
  k: Byte;
begin
  if (X1 = X2) and (Y1 = Y2) then Exit; {����յ���ͬ��������}
  Head := 1; Tail := 1; G := Maze; G[BX, BY] := 'B'; {��ʼ������ָ�룬������ʱ�ֿ��ͼ���������λ��}
  with Q[1] do {���ö���ͷ���}
    begin X := X2; Y := Y2; From := 0 end;
  while Head <= Tail do {�������������(X2,Y2)��(X1,Y1)�����·}
  with Q[Head] do
  begin
    for k := 1 to 4 do
      {(X-Dx[k], Y-Dy[k])�������G[X-Dx[k], Y-Dy[k]]�ǿո���δ����չ}
      if Valid(X-Dx[k], Y-Dy[k]) and (G[X-Dx[k], Y-Dy[k]]='.') then
      begin {��չ���}
        G[X-Dx[k], Y-Dy[k]] := 'Y'; {���G[X-Dx[k], Y-Dy[k]]�Ѿ�����չ}
        Inc(Tail);
        Q[Tail].X := X-Dx[k]; Q[Tail].Y := Y-Dy[k];
        Q[Tail].D := k; Q[Tail].From := Head;
        if (Q[Tail].X = X1) and (Q[Tail].Y = Y1) then {������㣬���·��}
        begin
          while Q[Tail].From <> 0 do
          begin
            Write(DName[Q[Tail].D]); {���Q[Tail].D��Ӧ�ġ��ߡ��ķ���}
            Tail := Q[Tail].From; {ת�������}
          end;
          Exit;
        end;
      end;
    Inc(Head); {Q[Head]��չ��ϣ���չ��һ�����}
  end;
end;

{��List[Node]������ƣ�������ߡ��͡��ơ�������}
procedure PrintSolution(Node: Word);
begin
  if List[Node].From=0 then {���ơ����е�һ��Ԫ��}
    with List[Node] do {����˴���㵽���ơ����е�һ��Ԫ���˵�λ�á��ߡ���·��}
      PrintWalk(SX, SY, X-Dx[D], Y-Dy[D], X, Y)
  else
    with List[Node] do
    begin
	  {�ݹ��������ơ�����ǰһ��Ԫ�صġ��ߡ��͡��ơ�������}
      PrintSolution(From);
{��������������ơ�����֮���˵�λ�á��ߡ���·��}
      PrintWalk(List[From].X, List[From].Y, X-Dx[D], Y-Dy[D], X, Y);
    end;
  Write(Upcase(DName[List[Node].D])); {���List[Node].D��Ӧ�ġ��ơ��ķ���}
end;

procedure Find; {Ѱ�Ҵ�(BX,BY)��(TX,TY)�����Ƶ����·}
var
  k: Byte;
begin
  Closed := 1;Open := 0; {��ʼ������ָ��}
  Expand(SX, SY, BX, BY); {�ҳ�������(BX,BY)ʱ���˴�(SX,SY)�ɴ�Ľ��}
  for k := 1 to 4 do
{���������(BX, BY)�����k���������Ƶ��ڽ��ķ�������(BX, BY, k)δ�����ɹ�������(BX-Dx[k], BY-Dy[k])��(SX,SY)�ɴ�}
if Mark[BX, BY, k] and (G[BX-Dx[k], BY-Dy[k]] = 'Y') then
begin {���ɶ���ͷԪ��}
      Inc(Open);
      with List[Open] do
        begin X := BX; Y := BY; D := k; From := 0 end;
      Mark[BX, BY, k] := False; {���(BX, BY, k)�Ѿ������ɹ���}
    end;
  while Closed<=Open do {�������������(BX,BY)��(TX,TY)�����·}
  begin
    with List[Closed] do
    begin
      BX := X+Dx[D]; BY := Y+Dy[D]; {�µ�����λ��}
      if (BX = TX) and (BY = TY) then {����Ŀ�����꣬������ߡ��͡��ơ�������}
        begin
{��List[Closed]������ƣ�������ߡ��͡��ơ�������}
PrintSolution(Closed);
Writeln;
Exit
end;
      Expand(X, Y, BX, BY); {�ҳ�������(BX,BY)ʱ���˴�(X,Y)�ɴ�Ľ��}
    end;
for k := 1 to 4 do
{���������(BX, BY)�����k���������Ƶ��ڽ��ķ�������(BX, BY, k)δ�����ɹ�������(BX-Dx[k], BY-Dy[k])��(SX,SY)�ɴ�}
      if Mark[BX, BY, k] and (G[BX-Dx[k], BY-Dy[k]] = 'Y') then
      begin {��չ���}
        Inc(Open);
        with List[Open] do
          begin X := BX; Y := BY; D := k; From := Closed end;
        Mark[BX, BY, k] := False; {���(BX, BY, k)�Ѿ������ɹ���}
      end;
    Inc(Closed); {List[Closed]��չ��ϣ���չ��һ�����}
  end;
  Writeln('Impossible.'); {���пգ������ܽ����Ӵ�����Ƶ��յ�}
end;

begin
  Assign(Input, 'pushing.in'); Reset(Input);
  Assign(Output, 'pushing.out'); Rewrite(Output);
  InputMaze; {����ֿ��ͼ}
  Find; {�������������������Ϸ�����Ž�}
  Close(Input);
  Close(Output);
end.
