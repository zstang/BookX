program street;

const
  MaxNode = 1000; {���·����}
  MaxDeg = 4; {ÿ��·��������ӵĽֵ���������һ�����͵�ϡ��ͼ}
  MaxEdge = MaxNode * MaxDeg div 2; {���ֵ���}

var
  G: array[1 .. MaxNode, 1 .. MaxDeg] of Integer;
  {ͼG�����ڽӱ�洢}
  Deg: array[1 .. MaxNode] of Integer;
  {ÿ������Ķ�������Ӧ·�����ӵĽֵ�����}

  Dfs: array[1 .. MaxNode] of Integer;
  {dfs[v]=c}
  Back: array[1 .. MaxNode] of Integer;
  {back[v]=����v��v�ĺ������׷�ݵ�����������ȵ��������ȱ�����}

  V_Stack, W_Stack: array[1 .. MaxEdge] of Integer;
  {v_stack,w_stack����¼������ȱ����������ıߵ�ջ}
  N_Stack: Integer;
  Dfn: Integer; {��ǰ������ȱ�����}

{��X��Y֮�еĽ�С��}
function Min(X, Y: Integer): Integer;
begin
  if X < Y then Min := X else Min := Y;
end;

{������ȣ���ͼG��ǿ��ͨ��֧}
procedure Bicomponent(V, Pred: Integer); {v��������ȱ����ĸ���pred����һ������}
var
  I, W, Count: Integer;
begin
  Inc(Dfn);  {��������һ���µĶ��㣬������ȱ�������һ}
  Dfs[V] := Dfn;  {���¸ö����������ȱ�����}
  Back[V] := Dfn;  {һ��ʼvֻ��׷�ݵ�v�Լ���û��·���ظ��ߵ�����}

  for I := 1 to Deg[V] do {��鶥��V�������ڽӶ���}
  begin
    W := G[V, I];
    if (Dfs[W] < Dfs[V]) and (W <> Pred) then
	begin
	  {����߻�δ���ı�}
	  V_Stack[N_Stack] := V;	{����<v.w>��ջ}
	  W_Stack[N_Stack] := W;
	  Inc(N_Stack);
	end;
	if Dfs[W] = 0 then	{w��δ���ʹ�����ǰ���}

	begin
	  Bicomponent(W, V); {��wΪ�����������������}
	  if Back[W] >= Dfs[V] then
	  begin
	    {�ҵ��µ�ǿ��ͨ��֧}
		Count := 0;	{countǿ��ͨ��֧�����Ķ�����}
		{���ǿ��ͨ��֧}
		while (V_Stack[N_Stack - 1] <> V) or (W_Stack[N_Stack - 1] <> W) do
		begin
          Writeln(V_Stack[N_Stack-1], ' ', W_Stack[N_Stack - 1]);
		  Dec(N_Stack);	{��ջ}
		  Inc(Count);
		end;
		Writeln(V_Stack[N_Stack - 1], ' ', W_Stack[N_Stack - 1]);
		if Count = 0 then
		  {�ҵ�һ��ֻ��һ���ߵ�ǿ��ͨ��֧}
		  Writeln(W_Stack[N_Stack - 1], ' ', V_Stack[N_Stack - 1]);
		Dec(N_Stack);
	  end
	  else
	    Back[V] := Min(Back[V], Back[W]);
	end
	else
	  {w�Ѿ�������}
	  Back[V] := Min(Back[V], Dfs[W]);
  end;
end;

var
  N, M, I, J, K: Integer;

begin
  Assign(Input, 'street.in');   {ָ�������ļ�}
  Reset(Input);
  Assign(Output, 'street.out'); {ָ������ļ�}
  Rewrite(Output);

  {��������}
  Readln(N, M);
  for I := 1 to N do Deg[I] := 0;
  for K := 1 to M do
  begin
    Readln(I, J);
    Inc(Deg[I]);
    Inc(Deg[J]);
    G[I, Deg[I]] := J;
    G[J, Deg[J]] := I;
  end;

  {��ʼ�����õĲ���}
  N_Stack := 1;
  Dfn := 0;
  for I := 1 to N do Dfs[I] := 0;

  {������������ͨ��֧��ͬʱ������}
  Bicomponent(1, -1);

  Close(Input);   {�ر������ļ�}
  Close(Output);  {�ر�����ļ�}
end.
