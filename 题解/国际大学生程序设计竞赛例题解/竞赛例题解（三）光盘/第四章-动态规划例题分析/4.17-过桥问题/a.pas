program bridge;
var
  fin,fout:text;   {�ļ�����}
  n,load,temp,len:integer; 
     {load���ŵ����أ�len���ŵĳ���}
  spd,wei:array[1..1001] of integer;
{spd��ų���������ٶȣ�wei��ų���������}
  da:array[1..1001] of double;
    {������da[i]��ʾǰi����ȫͨ��С�ŵ����ʱ��}
  i,j,k,tot,least:integer;
begin
  assign(fin,'bridge.in'); reset(fin);      {ָ����������ļ�}
  assign(fout,'bridge.out'); rewrite(fout);
  readln(fin,load,len,n);
  fillchar(da,sizeof(da),0);
  for i:=1 to n do begin
    readln(fin,wei[i],spd[i]);        {�����i����������}      
    if i=1 then da[1]:=len/spd[1]    {�߽�������ֻ��һ����}     
    else begin
      {����ǰi�������ŵ�������ʱ}
      j:=i;
      tot:=0;
      least:=30000;
      while j>=1 do begin           {j�Ƿ����λ��}
        inc(tot,wei[j]);             {tot�ǵ�ǰ�������}
        if tot>load then break;
        if least>spd[j] then least:=spd[j];       {least�������ĳ���}
        if tot<=load then
          {����da[j]+T(T�������˼·����)���뵱ǰda[i]�Ƚϣ��ó���Сֵ}
          if (da[i]=0) or (da[j-1]+len/least<da[i]) then
            da[i]:=da[j-1]+len/least         
          else
        else break;
        dec(j)                {������һ������λ��}
      end;
    end;
  end;
  writeln(fout,da[n]*60:0:1);   {������}
  close(fin); {�ر��ļ�}
  close(fout); {�ر��ļ�}
end.
