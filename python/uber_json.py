import json

class Solution(object):
    def __init__(self):
        self.map_list = []

    def flatten_json(self, json_str):
        d = json.loads(json_str)
        self.do_flatten_json(d)
        return '\n'.join(map(str, self.map_list))

    def do_flatten_json(self, d):
        if isinstance(d, list):
            map(self.do_flatten_json, d)
            return
            
        if not isinstance(d, dict):
            return

        if 'uuid' in d and 'properties' in d:
            self.map_list.append({
                'uuid': d['uuid'],
                'properties': d['properties']})

        for (key, value) in d.items():
            self.do_flatten_json(value)

j = '''
{
  "uuid": "abc",
  "properties": {
    "sessionName": "Test session name",
    "waypoints": [
      {"uuid": "def", "properties": {"latitude": 3}}
    ]
  }
}
'''

S = Solution()
print S.flatten_json(j)