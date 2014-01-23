function GenLogSuffixFromUnixTime() 
{
  local unix_time=$1
  local minute=`date -d @$unix_time +%M`
  minute=$(((10 + 10#$minute)%10))
  #minute=$(((10 + minute)%10))
  if [[ $minute -ge 5 ]]; then
    minute=$((minute - 5))
  fi
  unix_time=$(($unix_time - $minute*60))
  local time_str=`date -d @$unix_time +%Y%m%d.%H%M`
  echo $time_str
}
