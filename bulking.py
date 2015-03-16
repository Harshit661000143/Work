import os
import traceback
from elasticsearch import Elasticsearch

print '\n\n'
global title2
ES_HOST = {
    "host" : "localhost", 
    "port" : 9200
}

INDEX_NAME = 'hdokani2_index'
TYPE_NAME = 'doc'
address = "/Users/harshitdokania/Desktop/cs410/hdokani2_txt"
files = os.listdir(address)
print "length is "
print len(files)
bulk_data = []
for myid in range(2, len(files)):
  myfile = files[myid]
  count=1; 
  body= []
  with open(os.path.join(address, myfile), 'r') as txt_file:
       for line in txt_file:
           # dict[count]= line
           # print dict[count]
           line= line.replace('\n','')
           if(count>2):
               body.append(line)
           elif (count==1):
               url = line 
           elif (count==2):
               title = line
           count = count +1 
  op_dict = {
    "index" :{
              "_index": INDEX_NAME, 
               "_type": TYPE_NAME, 
               "doc_id": myfile
    }
  }
    
  data_dict= {
                "doc_id": myfile,
        	 "url": url,
                "title": title, 
                "body" : body 
  }
  bulk_data.append(op_dict)
  bulk_data.append(data_dict)
  es = Elasticsearch(hosts = [ES_HOST])
  if(myid%1000==0):
     print myid
     print("bulk indexing...")
     res = es.bulk(index = INDEX_NAME, body = bulk_data, refresh=True)
     print(" response: '%s'" % (res))  
     bulk_data=[]
'''
res = es.search(index = INDEX_NAME, size=2, body={"query": {"match_all": {}}})
print(" response: '%s'" % (res))  
print("results:")
for hit in res['hits']['hits']:
    print(hit["_source"])
#if es.indices.exists(INDEX_NAME):
#    print("deleting '%s' index..." % (INDEX_NAME))
#    res = es.indices.delete(index = INDEX_NAME)
#    print(" response: '%s'" % (res))
#
#print("creating '%s' index..." % (INDEX_NAME))
#res = es.indices.create(index = INDEX_NAME, type = TYPE_NAME)
#print(" response: '%s'" % (res))

  #print "We're on time %d" % (id)
  #print title
  #print url
'''
