#-*- coding: utf-8 -*-
''' Jieba func module.'''
import sys 
reload(sys)
sys.setdefaultencoding("utf-8")
import jieba.posseg as pseg

print(sys.getdefaultencoding())

def parse_test(p_str):
    ''' call jieba module to parse the text with tags, and transform
    the respective tag to NLPI forms.
    input: text string
    output: results with tags
    '''
    pseg.POSTokenizer(tokenizer=None)
    words = pseg.cut(p_str)
    ret_str = ''
    for word, flag in words:
        ret_str += word +'/' + flag + ' '
    return ret_str.encode('GB18030')

    # compat the tags

## test instance
# with open('test.txt') as f:
#     PSTR = f.read()
# PSTR = u"我爱天安门"
# TAGGED_STR = parse_test(PSTR)
# print(TAGGED_STR)

