#!/bin/python
import log
def main():
  log.set_logger(level='DEBUG')
  log.debug("hello world");
  log.info("info world");
  log.error("error world");
  pass
if __name__=='__main__':
  main()
