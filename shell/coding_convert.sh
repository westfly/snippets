#!/usr/bin/env bash
set -x
file_list=$*
tmp=$$.tmp
for file in $file_list
do
  iconv -futf-8 -tgbk $file > $tmp
  if [[ $? -ne 0 ]]; then
      echo "$file convert not right"
      continue;
  fi
  mv $tmp $file
done
if [[ -f $tmp ]]; then
  rm $tmp
fi
