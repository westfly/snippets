#!/bin/bash

#一个合法的表格应该包括
#表格名
#表格头
#数据(从数据文件中得到)
function GenerateTable()
{
  local header="$1"
  local title="$2"
  shift 2
  awk -v header="$header" -v title="$title" 'BEGIN{
    printf("<head><H3>%s</H3><head>\n",header)
    split(title,array, " "); 
    len = length(array);
    printf("<table border=\"1\" width=\"600\">\n");
    printf("<tr><th>seq</th>")
    for (i = 1; i <= len; ++i)
      printf("<th>%s</th>",array[i]);
  }{
    printf("<tr><td align=\"center\">%d</td>", NR);
    for(i = 1; i <=NF; ++i) {
      printf("<td align=\"center\"> %s</td>\n", $i);
    }
  }END{
  print "</table>";
}' $*
}
