machine_data="/search/odin/github/devbin/machine.dat"
#用于便捷的登陆机器，一个简单的封装
function match_internal()
{
  local machine=$1
  local num=$2
  ip_candidate=$(awk '{if ($1~/^#/)next; if($'"$num"'~/'"$machine"'/)print $1}' $machine_data)

  if [[ -z $ip_candidate ]]; then
    return -1
  fi
  arr=($ip_candidate)
  #len=${#ip_candidate[@]}
  len=${#arr[@]}
  count=0
  if [[ $len -gt 1 ]]; then
      x=0
      for ip in ${ip_candidate[@]}
      do
          echo "candidate $x,$ip"
          let x++
      done
      read -p "select " count
  fi
  echo $count, $len, ${arr[$count]}
  ssh ${arr[$count]}
}
#set -x
pattern=$1
match_internal $pattern 1
if [[ $? -ne 0 ]]; then
    match_internal $pattern 2
fi
