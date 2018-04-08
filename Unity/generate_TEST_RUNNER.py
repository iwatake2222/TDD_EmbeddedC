# -*- coding: utf-8 -*-
import sys
import os
import re


# find "TEST_GROUP(XXX);"
def get_test_group(lines):
	list_test_group = []
	for line in lines:
		obj_match = re.search(r"TEST_GROUP\s*\(\s*" , line)
		if obj_match:
			start = obj_match.end()
			obj_match = re.search(r"\s*\)" , line)
			if obj_match:
				end = obj_match.start()
				list_test_group.append(line[start:end])
				# print(line[start:end])
	return list_test_group

# find "TEST(XXX, YYY)""
def get_test_name(lines, test_group):
	list_test_name = []
	for line in lines:
		obj_match = re.search("TEST\s*\(\s*" +  test_group + "\s*,\s*", line)
		if obj_match:
			start = obj_match.end()
			obj_match = re.search(r"\s*\)" , line)
			if obj_match:
				end = obj_match.start()
				list_test_name.append(line[start:end])
				# print(line[start:end])
	return list_test_name

###
# Main
###
def main():
	if len(sys.argv) == 2:
		filename_input = sys.argv[1]
	else:
		print("invalid input filename")
		return
	f = open(filename_input)
	lines = f.readlines()
	f.close()

	### Analyze Code
	list_test = []	# [ ("GROUPA", [TEST_CASE1, TEST_CASE2]), ]
	list_test_group = get_test_group(lines)
	for test_group in list_test_group:
		group_name = get_test_name(lines, test_group)
		list_test.append((test_group, group_name))

	### Print TEST_GROUP_RUNNER
	# TEST_GROUP_RUNNER(FakeTimeService)
	# {
	# 	RUN_TEST_CASE(FakeTimeService, Create);
	# 	RUN_TEST_CASE(FakeTimeService, Set);
	# }
	for test_group in list_test:
		print("TEST_GROUP_RUNNER({0})".format(test_group[0]))
		print("{")
		for test_name in test_group[1]:
			print("\tRUN_TEST_CASE({0}, {1});".format(test_group[0], test_name))
		print("}")

	print("---------------------------------------")
	for test_group in list_test:
		print("RUN_TEST_GROUP({0});".format(test_group[0]))

###
# Main
###
if __name__ == "__main__":
	main()
