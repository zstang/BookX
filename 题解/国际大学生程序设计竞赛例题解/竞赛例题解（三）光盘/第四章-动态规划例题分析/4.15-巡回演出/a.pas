{$i-,r-,x-,v-,s-,f-,b-,n+}
var
  day,i,i1,j,k,n:integer;
  f1,f2:text;
  cost:array[1..1000,1..10] of longint;
     {cost[n][i]��ʾ��n�쵽�����i�����ٷ���}
  d,cnt:array[1..10,1..10] of byte;
     {d[i][j]��ʾ��i��j�ж��ٺ���}
  price:array[1..10,1..10,1..30] of longint;
     {price[i][j]��¼��i��j��ÿһ������ķ���}

procedure init;    {ָ���������}
begin
  assign(f1,'perform.dat');   {ָ����������ļ�}
  reset(f1);
  assign(f2,'perform.out');
  rewrite(f2);
end;

procedure read_file;         {�������ļ�}
begin
  readln(f1,n,k);
  if n>=2 then
    for i:=1 to n do    {���뺽���}
      for j:=1 to n do
        if i<>j then
          begin
            read(f1,d[i,j]);   {���뺽��ѭ������}
            for i1:=1 to d[i,j] do read(f1,price[i,j,i1]); {���뺽�����仯}
          end;
end;

procedure run; {������}
begin
  repeat
    read_file;     {��������}
    if n>=2 then
      begin
        fillchar(cost,sizeof(cost),0);  {cost[i][j]=0��ʾ��ʱû�е���j��·��}
        for i:=2 to n do cost[1,i]:=price[1,i,1];  {��ʼ����}
        day:=1;
        fillchar(cnt,sizeof(cnt),1);
        while day<k do  {���������ֽ׶Σ�day��������ֱ��k}
          begin
  {CNT�����¼�˵�DAY��ʱ�������ѭ������һ�죬����������CNT����Ԫ��ѭ����1}
            for i:=1 to n do       
              for j:=1 to n do
                if i<>j then
                  begin
                    inc(cnt[i,j]);
                    if cnt[i,j]>d[i,j] then cnt[i,j]:=1;
                  end;
           {��COST[DAY,I]�Ƴ�COST[DAY+1,J] (I,J=1,2,��,N)}
            for i:=1 to n do
              if cost[day,i]>0 then   {��day���ܹ�����i}
                for j:=1 to n do
                  if (i<>j) and (price[i,j,cnt[i,j]]>0) then
                                        {��day+1���к����i��j}
                    if (cost[day+1,j]=0)
                      or (cost[day,i]+price[i,j,cnt[i,j]]<cost[day+1,j]) then
               {������µ�·�����߷��ø��٣���ô���ҵ�һ���µ����мƻ�}
                      cost[day+1,j]:=cost[day,i]+price[i,j,cnt[i,j]];
            inc(day);     {����������һ��ļƻ�}
          end;
        writeln(f2,cost[k,n]);  {������}
      end;
  until n=0;   {֪���������}
end;

procedure done; {�ر��������}
begin
  close(f1); {�ر��ļ�}
  close(f2); {�ر��ļ�}
end;

begin  {������}
  init;  {ָ���������}
  run;   {������}
  done;  {�ر��������}
end.
